      program multichannel_wp_propagation
      use parameters
      implicit none
      character(LEN=900) dummy
      integer        i,j,k,n,iteration,data_number(1:2)
      complex*16     WP(1:3,NGRID),WP_AVG(1000,NGRID) !! 1000 x NGRID costs ~154MB
      complex*16     K1(1:3,NGRID),K2(1:3,NGRID),K3(1:3,NGRID),K4(1:3,NGRID)
      real*8         progress,time,flux(1:2,1d4),fluxSUM,norm,V(1:10,1:10),temp(10)

	!! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      !! input electronic potential energy surface matrix W (off-diag. = coupling)
	!! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      W = 0.0d0
	open(101,FILE='output/pes.txt')
      do i=1,NGRID
	  progress = (Ri+real(i)*dR)
        call POTIBR(V,progress)
	  do j=1,3
	  do k=1,3
	   W(j,k,i) = V(j,k)
	  enddo
	  enddo

        if(progress .ge. 10.0d0 .and. progress .le. 23.0d0)then
	    W(2,2,i) = 0.0d0
	  endif
	  !W(2,2,i) = exp(-(progress-2.85d0)/0.7d0)

	  if(progress .ge. 23.0d0)then !! negative imaginary absorbing boundary
	    W(2,2,i) = -ImI*0.3d0*((progress-23.0d0)/2.0d0)**2
	    W(3,3,i) = -ImI*0.3d0*((progress-23.0d0)/2.0d0)**2
	  endif

	  W(3,3,i) = W(3,3,i) + 3685.0d0*cmi!! separation between 2p Br/Br* atomic states (1932)

	  temp(1) = real(W(1,1,i))
	  temp(2) = real(W(2,2,i))+aimag(W(2,2,i))
	  temp(3) = real(W(3,3,i))+aimag(W(3,3,i))
	  temp(4) = real(W(2,3,i))
	  write(101,'(20(E22.15,3x))') progress,(temp(j),j=1,4)
      enddo
	close(101)

	!! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	!! read in eigenstates in the B manifold
	!call readin_eigenstates(0)
	!! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	!! >>>>>>>>>>>>>>>>>>>>>>>>>>>>
      !! >>>  program loop starts >>>
	!! >>>>>>>>>>>>>>>>>>>>>>>>>>>>
	flux = 0.0d0
      WP_AVG = 0.0d0
	!! >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      do iteration=1,1
	data_number(1) = 1000
	data_number(2) = 1000
	print *, "iteration #",iteration,":"

	!! initialize field
      print *, "initializing field..."
      call make_ps_field(1d0,iteration)
	print *, "field initialized."

	!open(101,file='output/field.txt')
	!do i=1,NPROP
	!  write(101,*) real(i)*dT/fs,field(2*i)
	!enddo
	!close(101)

      !! specify initial WP as ground PES ground eigenstate
      !! note: pre-diagonalized wave functions are the "u(R)"-radial functions
      WP = 0.0d0
      open(101,FILE='input/eigenvectors.txt')
      do n=1,600
        read(101,*) dummy,WP(1,n)
      enddo
      close(101)

      !open(102,FILE='output/initial.txt')
      !do n=1,NGRID
      !  write(102,'(4(F22.15,3x))') real(n-1)*dR+Ri,abs(WP(1,n))**2
      !enddo
      !close(102)

	!!---------------------------------------------------
      !! propagate wave packets with RK4 accuracy
	!!---------------------------------------------------
	print *, "starting propagation..."
      do i=1,NPROP!%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

       time = real(i)*dT
       K1   = dT*DWP(WP, field(2*i))
       K2   = dT*DWP(WP+K1/2.0d0, field(2*i+1))
       K3   = dT*DWP(WP+K2/2.0d0, field(2*i+1))
       K4   = dT*DWP(WP+K3, field(2*i+2))
       WP   = WP + (K1 + 2.0d0*K2 + 2.0d0*K3 + K4)/6.0d0

       if(mod(i,NPROP/10)==0.0d0)then
        print *, 100*i/NPROP,"% done"
       endif

       if(mod(i,NPROP/data_number(1))==0.0d0)then
	  k = i/(NPROP/data_number(1))

	  j = 1100
	  flux(1,k) = flux(1,k) + aimag(conjg(WP(2,j))*(WP(2,j+1)-WP(2,j-1))/(2.0d0*dR))/MASS
	  flux(2,k) = flux(2,k) + aimag(conjg(WP(3,j))*(WP(3,j+1)-WP(3,j-1))/(2.0d0*dR))/MASS

	  !fluxSUM = fluxSUM + flux * TPROP/real(data_number(1))
	  !write(198,*) iteration,time/fs,flux

        !norm = 0.0d0
        !do k=1,NGRID
        !  norm = norm + (abs(WP(1,k))**2)*dR
        !enddo
        !write(200,*) iteration,time/fs,norm

	  !call project_to_B(WP,k)

       endif

       !! sum up wave packet magnitudes
       if(mod(i,NPROP/data_number(2))==0.0d0)then
        do n=1,NGRID
          temp(1) = abs(WP(2,n))**2+abs(WP(3,n))**2
          WP_AVG(i/(NPROP/data_number(2)),n) = WP_AVG(i/(NPROP/data_number(2)),n) + temp(1)
        enddo
       endif

      enddo!%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

      !! calculate final norm of ground PES wave function
	!norm = 0.0d0
	!do j=1,NGRID
      !  norm = norm + (abs(WP(1,j))**2)*dR
      !enddo
	!write(199,*) iteration,norm,fluxSUM

	           !! <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	enddo      !! <<<<<<<<<<<<  program loop ends <<<<<<<<<<<<
	           !! <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

      open(102,FILE="data-wp-wide.txt")
      do i=1,data_number(2)
       do j=1,NGRID
        temp(1) = real(j-1)*dR+Ri
        temp(2) = real(i)*(TPROP/data_number(2))/fs
        temp(3) = WP_AVG(i,j)/real(iteration)
        write(102,'(20(F22.15,3x))') temp(1),temp(2),temp(3)
       enddo
       write(102,*) ''
      enddo
      close(102)

      open(198,FILE='data-flux-wide.txt')
	do i=1,data_number(1)
	  temp(1) = flux(1,i)/real(iteration)
	  temp(2) = flux(2,i)/real(iteration)
	  write(198,'(3(E22.15,3x))') real(i)*(TPROP/fs)/real(data_number(1)),temp(1),temp(2)
	enddo
      close(198)

	!do j=1,27
	! do i=1,data_number(1)
      !   temp(1) = real(i)*(TPROP/fs)/real(data_number(1))
      !   temp(2) = coefficientsB(j,i,1)/real(iteration)
      !   temp(3) = coefficientsB(j,i,2)/real(iteration)
	!   write(198,'(4(E22.15,3x))') real(j),temp(1),temp(2),temp(3)
	! enddo
	! write(198,*) ""
	! write(198,*) ""
	!enddo


      CONTAINS
      !!=====================================================================================
      function DWP(WP,efield) !! = Hamiltonian * WP
      use parameters
      implicit none
      complex*16,dimension(1:3,NGRID) :: WP,DWP
      real*8     progress
      complex*16 efield,KE,PE,T1,T2,T3

      DWP    = 0.0d0
      do n=2,NGRID-1
         progress = real(n-1)*dR + Ri
         KE       = (WP(1,n-1)-2.0d0*WP(1,n)+WP(1,n+1))/(dR**2)
         KE       = -KE/(2.0d0*MASS)
         PE       = W(1,1,n) * WP(1,n)
	   T1       = KE+PE
	   T2       = -efield*W(1,2,n)*WP(2,n)
	   T3       = -efield*W(1,3,n)*WP(3,n)
         DWP(1,n) = -ImI*(T1+T2+T3)
      enddo

      do n=2,NGRID-1
         progress = real(n-1)*dR + Ri
         KE       = (WP(2,n-1)-2.0d0*WP(2,n)+WP(2,n+1))/(dR**2)
         KE       = -KE/(2.0d0*MASS)
         PE       = 1.0d0/(MASS*progress**2)
         PE       = PE + W(2,2,n) 
         PE       = PE * WP(2,n)
	   T2       = KE+PE
	   T1       = -efield*W(2,1,n)*WP(1,n)
	   T3       = W(2,3,n)*WP(3,n)
         DWP(2,n) = -ImI*(T1+T2+T3)
      enddo

      do n=2,NGRID-1
         progress = real(n-1)*dR + Ri
         KE       = (WP(3,n-1)-2.0d0*WP(3,n)+WP(3,n+1))/(dR**2)
         KE       = -KE/(2.0d0*MASS)
         PE       = 1.0d0/(MASS*progress**2)
         PE       = PE + W(3,3,n) 
         PE       = PE * WP(3,n)
	   T3       = KE+PE
	   T1       = -efield*W(3,1,n)*WP(1,n)
	   T2       = W(3,2,n)*WP(2,n)
         DWP(3,n) = -ImI*(T1+T2+T3)
      enddo

      end function
      !!=====================================================================================

      end
