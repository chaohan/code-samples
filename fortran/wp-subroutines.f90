
      !!=====================================================================================
      !!=====================================================================================
      module parameters
      complex*16,parameter :: ImI    = (0.0d0,1.0d0)
      real*8,parameter     :: PI     = 3.1415926d0
      real*8,parameter     :: WCM    = 0.3d-16                  !! w/cm^2
      real*8,parameter     :: cmi    = 4.556335d-6              !! 1cm^-1 in hartree
      real*8,parameter     :: epc    = 137.0d0/(4.0d0*PI)       !! c*epsilon_0
      real*8,parameter     :: E0     = 0.5d0*sqrt(4d13*WCM/epc)
      real*8,parameter     :: E1     = sqrt(1d3*WCM/epc)
      real*8,parameter     :: E2     = sqrt(0.001d0*WCM/epc)
      real*8,parameter     :: fs     = 1.0d0/0.024d0            !! 1fs in a.u.
      real*8,parameter     :: MASS   = 89380.0d0                !! IBr reduced mass (wolfram)
      real*8,parameter     :: kBT    = 0.0183675d0              !! kB*(5800K) in hartree

      integer,parameter    :: NGRID  = 2100                     !! # of grid points in R
      real*8,parameter     :: dR     = 0.01d0
      real*8,parameter     :: Ri     = 4.0d0
      real*8,parameter     :: TPROP  = 20.0d3*fs                !! 100 points per 1fs
      integer,parameter    :: NPROP  = 2.0d6                    !! note: need 1d6 for 10ps
      real*8,parameter     :: dT     = TPROP/real(NPROP)
      real*8,parameter     :: dOmega = 0.1*cmi

      complex*16,dimension(1:3,1:3,NGRID)   :: W
      complex*16,dimension(NPROP*2+10)      :: field            !! make extra slots for RK4
      real*8,dimension(2000)                :: spectrum
      complex*16,dimension(30,NGRID)        :: eigenstatesB
      real*8,dimension(1:30,1:1000,1:2)     :: coefficientsB

      contains
      !!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      real*8 function epsilon(t)
      implicit none
      real*8 t
      epsilon = exp(-0.5d0*(t-10d3*fs)**2/(3d3*fs)**2)!/sqrt(sqrt(PI)*3d3*fs)
      !epsilon = 1d0/(exp(-(t-0.25d3*fs)/(0.03d3*fs))+1d0)
      !epsilon = 1d0/(exp(-(8d3*fs-t)/(0.2d3*fs))+1d0)
      end function epsilon
      !!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      real*8 function s0(omega)
      implicit none
      real*8 omega
      !s0 = (E1/dOmega)*exp(-0.5d0*(omega-17950.0d0*cmi)**2/(30.0d0*cmi)**2)
      s0 = E1*exp(-0.5d0*(omega-17700.0d0*cmi)**2/(300.0d0*cmi)**2)
      !s0 = sqrt(0.0161404d0)*(E1/dOmega)*exp(-0.5d0*(omega-17950.0d0*cmi)**2/(30.0d0*cmi)**2)
      end function s0

      end module parameters
      !!=====================================================================================
      !!=====================================================================================


      !!====================================================================
      !!   Gaussian random number generator
      !!   "call random_seed()" before calling this subroutine.
      !!====================================================================
      subroutine G_RNG(mean,sigma,output)
      implicit none
      real*8  mean,sigma,gauss,output,var(1:2)

      do
       call random_number(var)
       var(1) = 4.0d0*sigma*(2.0d0*var(1)-1.0d0)
       gauss = exp(-0.5d0*(mean+var(1))**2/(sigma**2))
       if(var(2).le.gauss)then
         exit
       endif
      enddo

      output = var(1)
      end subroutine

 	!!====================================================================
	!!   Doppler spectral amplitude random variable generator
      !!   "call random_seed()" before calling this subroutine.
      !!====================================================================
 	subroutine D_RNG(mean,output)
      use parameters
      implicit none
      real*8  mean,pdf,output,var(1:2)

      do
       call random_number(var)
       var(1) = var(1)*4d0*mean
	 var(2) = var(2)*sqrt(PI/2d0)*exp(-0.5d0)/mean
       pdf = 2d0*var(1)*PI/(4d0*mean**2) * exp(-var(1)**2*PI/(4d0*mean**2))
       if(var(2).le.pdf)then
         exit
       endif
      enddo

      output = var(1)
      end subroutine

	!!====================================================================
	!!   collision phase-jump time random variable generator
      !!   "call random_seed()" before calling this subroutine.
      !!====================================================================
	subroutine C_RNG(mean,output)
      use parameters
      implicit none
      real*8  mean,pdf,output,var(1:2)

      do
       call random_number(var)
       var(1) = var(1)*10d0*mean
	 var(2) = var(2)/mean
       pdf = exp(-var(1)/mean)/mean
       if(var(2).le.pdf)then
         exit
       endif
      enddo

      output = var(1)
      end subroutine

	!!====================================================================
      !!   make collision broadened field
      !!====================================================================
	subroutine make_c_field(tauc,omega)
      use parameters
      implicit none
	integer Nemitter,i,j,k
	real*8 tauc,omega,tickers(10000),angles(10000),time,temp

	field    = 0.0d0
	Nemitter = 1000

	call random_seed()
	do j=1,Nemitter
 	 call C_RNG(tauc,tickers(j))
	enddo
	call random_number(angles)
	angles = 2d0*PI*angles

      do i=1,size(field)
	 field(i) = 0.0d0	
       time     = real(i)*dT/2.0d0
	 do j=1,Nemitter
	   if(time.ge.tickers(j))then
	     call C_RNG(tauc,temp)
	     tickers(j) = tickers(j) + temp
	     call random_number(angles(j))
	     angles(j) = 2d0*PI*angles(j)
	   endif
	   field(i) = field(i) + exp(ImI*angles(j))
	 enddo
	 field(i) = E2*epsilon(time)*field(i)*exp(-ImI*omega*time)
	 !field(i) = E2*field(i)*exp(-ImI*omega*time)
	enddo

	end subroutine

      !!====================================================================
      !!   phase-shaped (solar) field (deterministic power spectrum)
      !!====================================================================
      subroutine make_ps_field(signal,iteration)
      use parameters
      implicit none
      integer i,j,iteration
      real*8 signal,omega,time,phases(1d5)
      complex*16 efield

      field = 0.0d0
      call random_seed()
      call random_number(phases)
      phases = signal*2.0d0*PI*phases
      !do i=1,size(phases)
      !  call G_RNG(0d0,signal*PI,phases(i))
      !enddo

      do i=1,size(field)
       time = real(i)*dT/2.0d0
       do j=16400,18400
         omega  = real(j)*cmi
         !efield = (omega**3/(4d0*PI**3*137d0**2))/(exp(omega/kBT)-1d0)
         !efield = sqrt(1d0*cmi*efield/epc)
         !efield = efield * exp(-ImI*(omega*(time-2d3*fs)+phases(j)))
         efield = s0(omega)*exp(-ImI*(omega*(time-2d3*fs)+phases(j)))
         field(i) = field(i) + efield
       enddo

       if(mod(i,size(field)/10)==0.0d0)then
         print *, 100*i/size(field),"% done"
       endif

       field(i) = field(i)*epsilon(time)
      enddo
      end subroutine

      !!====================================================================
      !!   Calculates the power spectrum from the field autocorrelation
      !!====================================================================

      subroutine powerspec(null)
      use parameters
      implicit none
      integer null,i,j,k
      real*8 delay
      complex*16 integral,autocorr(-1000:1000)

      do i=-1000,1000
        delay    = real(i)*0.01d0*fs
        k        = delay/(dT/2d0)
        integral = 0.0d0
        do j=abs(k),size(field)-abs(k)
          integral = integral + conjg(field(j))*field(j+k)
        enddo
      enddo

      end subroutine

      !!====================================================================
      !!   Calculate the power spectrum from Fourier transform,
      !!   and add to the "spectrum" array for further averaging
      !!====================================================================
      subroutine add_to_spectrum(null)
      use parameters
      implicit none
      integer null,j,k
      real*8 E
      complex*16 fourier

      do j=1,500!200
        !E = (real(j)*0.1d0 + 17854.0d0)*cmi
        E = real(j)*100d0*cmi
        fourier = 0.0d0
        do k=1,size(field)
          fourier = fourier + field(k)*exp(ImI*E*real(k)*dT/2d0)
        enddo
        spectrum(j) = spectrum(j) + (abs(fourier)*dT/2d0)**2

        !if(mod(j,200)==0.0d0)then
        !  print *,j/20,"% spectrum done"
        !endif
      enddo

      end subroutine
      !!====================================================================
      !!   Calculates the overlap to B manifold eigenstates
      !!====================================================================
	subroutine readin_eigenstates(null)
      use parameters
      implicit none
	integer i,j,null
	real*8 dummy

	open(123,FILE="input/eigenvectors-B.txt")
	do i=1,NGRID
	  read(123,*) dummy, (eigenstatesB(j,i),j=1,27)
	enddo
	close(123)

	coefficientsB = 0.0d0

	end subroutine
	!! -------------------------------------------------------------
	subroutine project_to_B(WP,k)
      use parameters
      implicit none
	complex*16 WP(1:3,NGRID),integral
	integer i,j,k

	do i=1,27
	  integral = 0.0d0
	  do j=1,1000
	    integral = integral + eigenstatesB(i,j)*WP(3,j)
	  enddo
        integral = integral*dR
	  coefficientsB(i,k,1) = coefficientsB(i,k,1) + abs(integral)**2
	  coefficientsB(i,k,2) = coefficientsB(i,k,2) + atan2(aimag(integral),real(integral))
	enddo

	end subroutine

