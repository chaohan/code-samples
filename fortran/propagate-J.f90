      !!=====================================================================================
      !! Attention:
      !! (1) check NGRID consistancy with the eigenvector diagonalization program
      !!     as well as when expanding the internuclear distance R range for propagation
      !! (2) the temporal propagation is done in the reference frame of the pulse, thus
      !!     time origin t=0 is always set as the peak of the pulse. so, the literal "t_c"
      !!     is set zero, but reflected in the initial wave packet as "tdelay"
      !! (3) the peak intensity in time is calculated as the peak Poynting vector magnitude
      !!     of the electric field, hence the c*epsilon_0 factor
      !!=====================================================================================
      module parameters
      complex*16,parameter :: ImI       = (0.0d0,1.0d0)
      real*8,parameter     :: PI        = 3.1415926d0
      real*8,parameter     :: epc       = 137.0d0/(4.0d0*PI)!! c*epsilon_0
      real*8,parameter     :: TWCMS     = 0.3d-4  !! 1TW/cm^2 in a.u.
      real*8,parameter     :: femtosec  = 1.0d0/0.024d0 !! 1 fs in a.u.
      real*8,parameter     :: MASS      = 918.0d0 !! reduced mass for H2+
      integer,parameter    :: JMAX      = 10      !! cut-off J value
      integer,parameter    :: NGRID     = 1000    !! # of grid points in R
      real*8,parameter     :: dR        = 0.02d0
      real*8,parameter     :: omegaL    = 0.15d0
      real*8,parameter     :: tp        = 3.0d0*femtosec !! 1/(3fs) = 0.008 au
      real*8,parameter     :: TPROP     = 30.0d0*femtosec
      integer,parameter    :: NPROP     = 5.0d4   !! note: 1d3 fails for 60fs duration
      real*8,parameter     :: dT        = TPROP/real(NPROP)
      real*8,dimension(-1:1,NGRID)      :: W
      real*8,dimension(1:NGRID)         :: tdipole
      real*8                       :: tdelay
      real*8                       :: intensity
      end module
      !!=====================================================================================
      program multichannel_wp_propagation
      use parameters
      implicit none
      character(LEN=900) dummy
      integer            i,j,n
      complex*16         WP(0:JMAX,NGRID),PSI_i(0:20,NGRID)
      complex*16         K1(0:JMAX,NGRID),K2(0:JMAX,NGRID)
      complex*16         K3(0:JMAX,NGRID),K4(0:JMAX,NGRID)
      complex*16         summ,PPL(1:100),temp(NGRID)
      real*8             progress,time,efield(1:2*NPROP)

      open(199,FILE="data-scan-continuum.txt")
      do intensity=100.0d0*TWCMS,100.0d0*TWCMS,20.0d0*TWCMS
      write(199,*) ""
      write(199,*) "# delay scan, intensity = ",intensity/TWCMS, "TW/cm^2"
      !write(199,*) "# tdelay = ",tdelay/femtosec, "fs"
      write(199,*) ""
      do tdelay=0.0d0*femtosec,2.0d0*femtosec,1.0d0*femtosec

      !! read in PES from file, note that R starts at 1 Bohr
      W = 0.0d0
      open(101,FILE="input/pes-out.txt")
      open(102,FILE="output/pes.output")
      do n=1,1000
       read(101,*)  progress,W(1,n),W(-1,n)
       write(102,*) progress,W(1,n),W(-1,n)
      enddo
      close(101)
      close(102)

      !! read in transition dipole from file
      tdipole = 0.0d0
      do i=1,NGRID
         tdipole(i) = -(real(i-1)*dR + 1.0d0)/2.0d0 !! approximation D(R) = -R/2
      enddo
      open(101,FILE='input/pes-all.txt')
      read(101,*) dummy
      do i=1,700
         read(101,*) dummy,dummy,dummy,tdipole(i) !! Gaussian09 values
      enddo
      close(101)

      !! read in eigenstates, and specify initial wave packet
      PSI_i = 0.0d0
      WP    = 0.0d0
      open(101,FILE="input/eigenvectors.txt")
      do n=1,1000
        read(101,*)  dummy,(PSI_i(i,n),i=0,10)
      enddo
      close(101)

      open(101,FILE="output/initialWP.output")
      do n=1,NGRID
        WP(0,n) = PSI_i(4,n)*exp(ImI*(-0.060481d0)*(TPROP/2.0d0-tdelay))/sqrt(3d0)
        WP(0,n) = PSI_i(5,n)*exp(ImI*(-0.052687d0)*(TPROP/2.0d0-tdelay))/sqrt(3d0)+ WP(0,n)
        WP(0,n) = PSI_i(6,n)*exp(ImI*(-0.045427d0)*(TPROP/2.0d0-tdelay))/sqrt(3d0)+ WP(0,n)
        write(101,'(4(F22.15,3x))') real(n-1)*dR+1.0d0,abs(WP(0,n))**2
        !write(199,'(4(E22.15,3x))') real(n-1)*dR+1.0d0,tdelay/femtosec,abs(WP(0,n))**2
      enddo
      close(101)

      !! propagate the initial wp on the J=1 continuum
      !do time=0.0d0,tdelay,tdelay/1.0d4
      !   K1   = tdelay/1.0d4*DWP(WP,0.0d0)
      !   K2   = tdelay/1.0d4*DWP(WP+K1/2.0d0,0.0d0)
      !   K3   = tdelay/1.0d4*DWP(WP+K2/2.0d0,0.0d0)
      !   K4   = tdelay/1.0d4*DWP(WP+K3,0.0d0)
      !   WP   = WP + (K1+2.0d0*K2+2.0d0*K3+K4)/6.0d0
      !enddo

      !open(101,FILE="output/initialWP-proped.output")
      !do n=1,NGRID
      ! write(101,'(4(F22.15,3x))') real(n-1)*dR+1.0d0,abs(WP(0,n))**2
      !enddo
      !close(101)

      !! make the shaped-electric-field array
      efield = 0.0d0
      do i=1,2*NPROP
         time = real(i)*0.5d0*dT - TPROP/2.0d0
         !! uncomment to use this for arbitrary spectral shaping
         summ  = 0.0d0
         do j=0,1000
            progress  = real(j)*(8.0d0/tp)/1000.0d0 - 4.0d0/tp
            summ       = summ + spectrum(progress)*exp(ImI*progress*time)
         enddo
         summ = summ * ((8.0d0/tp)/1000.0d0)/sqrt(2.0d0*PI)
         efield(i) = real(summ*exp(-ImI*omegaL*time))

         !! uncomment to use for time-domain TL pulse
         !efield(i) = exp(-(time-12.0d0*femtosec)**2/(2.0d0*tp**2))*cos(omegaL*time)
         !efield(i) = efield(i) + exp(-(time+12.0d0*femtosec)**2/(2.0d0*tp**2))*cos(omegaL*time+CEP)
         !efield(i) = efield(i)*sqrt(intensity)
      enddo
      open(101,FILE='output/field.output')
      do i = 0,1000
         write(101,*) (i*TPROP/1000-TPROP/2)*0.024,efield(int(real(i)*2*NPROP/1000.0d0))
      enddo
      close(101)

      !! propagate wave packets with RK4 accuracy
      do i=1,NPROP
       time = real(i)*dT - TPROP/2.0d0
       K1   = dT*DWP(WP, efield(2*i))
       K2   = dT*DWP(WP+K1/2.0d0, efield(2*i+1))
       K3   = dT*DWP(WP+K2/2.0d0, efield(2*i+1))
       K4   = dT*DWP(WP+K3, efield(2*i+2))
       WP   = WP + (K1 + 2.0d0*K2 + 2.0d0*K3 + K4)/6.0d0

       if(mod(i,NPROP/2)==0.0d0)then
        print *, 50*i/(NPROP/2),"% done, check:",abs(WP(0,321))
       endif
      enddo

      !! output the final wave packet
      open(101,FILE="output/wp.output")
      do n=1,NGRID
        write(101,'(50(F22.15,3x))') real(n-1)*dR+1.0d0,(abs(WP(j,n)**2),j=0,JMAX)
      enddo
      close(101)

      !! calculate and output the final populations in selected channels
      PPL = 0.0d0
      do n=1,NGRID
         PPL(1)  = PPL(1)  + conjg(PSI_i(3,n))*WP(0,n)*dR
         PPL(2)  = PPL(2)  + conjg(PSI_i(4,n))*WP(0,n)*dR
         PPL(3)  = PPL(3)  + conjg(PSI_i(5,n))*WP(0,n)*dR
         PPL(4)  = PPL(4)  + conjg(PSI_i(6,n))*WP(0,n)*dR
         PPL(5)  = PPL(5)  + conjg(PSI_i(7,n))*WP(0,n)*dR
         PPL(6)  = PPL(6)  + (abs(WP(0,n))**2)*dR
         PPL(7)  = PPL(7)  + (abs(WP(1,n))**2)*dR
         PPL(8)  = PPL(8)  + (abs(WP(2,n))**2)*dR
         PPL(9)  = PPL(9)  + (abs(WP(3,n))**2)*dR
         PPL(10) = PPL(10) + (abs(WP(4,n))**2)*dR
         PPL(11) = PPL(11) + (abs(WP(5,n))**2)*dR
         PPL(12) = PPL(12) + (abs(WP(6,n))**2)*dR
         PPL(13) = PPL(13) + (abs(WP(7,n))**2)*dR
         PPL(14) = PPL(14) + (abs(WP(8,n))**2)*dR
         PPL(15) = PPL(15) + (abs(WP(9,n))**2)*dR
         PPL(16) = PPL(16) + (abs(WP(10,n))**2)*dR
      enddo
      PPL(1) = abs(PPL(1))**2
      PPL(2) = abs(PPL(2))**2
      PPL(3) = abs(PPL(3))**2
      PPL(4) = abs(PPL(4))**2
      PPL(5) = abs(PPL(5))**2
      write(199,'(20(F22.15,3x))'), tdelay/femtosec,(abs(PPL(i)),i=1,16)
      !write(199,'(20(F22.15,3x))'), intensity/TWCMS,(abs(PPL(i)),i=1,16)

      enddo
      enddo
      close(199)

      CONTAINS
      !!=====================================================================================
      function DWP(WP,efield)
      use parameters
      implicit none
      complex*16,dimension(0:JMAX,NGRID) :: WP,DWP
      real*8     progress,efield
      complex*16 KE,PE,VR,VL

      DWP    = 0.0d0
      do j=0,JMAX
      do n=2,NGRID-1
         progress = real(n-1)*dR + 1.0d0 ! starting at R=1Bohr
         KE       = (WP(j,n-1)-2.0d0*WP(j,n)+WP(j,n+1))/(dR**2)
         KE       = -KE/(2.0d0*MASS)
         PE       = real(j)*real(j+1)/(2.0d0*MASS*progress**2)
         PE       = PE + W((-1)**j,n) 
         PE       = PE * WP(j,n)
         VR       = 0.0d0
         VL       = 0.0d0
         if(j.ne.JMAX)then
          VR      = tdipole(n) *efield*WP(j+1,n)
          VR      = VR * yy(j,0)
         endif
         if(j.ne.0)then
          VL      = tdipole(n) *efield*WP(j-1,n)
          VL      = VL * yy(j-1,0)
         endif
         DWP(j,n) = -ImI*(KE+PE+VR+VL)
      enddo
      enddo
      end function
      !!=====================================================================================
      complex*16 function spectrum(w)
      use parameters
      implicit none
      real*8 w,PHASE

      PHASE    = 0.0d0
      spectrum = tp*sqrt(intensity/epc)
      spectrum = spectrum * exp(-(tp*w)**2/2.0d0- ImI*PHASE)

      end function
      !!=====================================================================================
      real*8 function yy(JI,MI)
      use parameters
      implicit none
      integer JI,MI
      real*8 J,M
        J  = real(JI)
        M  = real(MI)
        yy = -sqrt((J+1.0d0-M)*(J+1.0d0+M)/((2.0d0*J+1.0d0)*(2.0d0*J+3.0d0)))
        !sqrt((2.0d0*J+3.0d0)/(J+M+1.0d0))
        !yy = yy * ((J-M+1.0d0)/(2.0d0*J+1.0d0))**1.5d0
      end function
      !!=====================================================================================
      end
