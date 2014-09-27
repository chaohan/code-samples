      program wp_propagator
      implicit none

      character(1000) dummy
      character(100)  filename
      integer    i,k,l,m,loop,NGRID,J,nu,Nout
      complex*16 ImI,pulse,rho(2,2)
      complex*16 edipole(1002),PSI_G(1002),RPSI_G(1002)
      complex*16 WPA(1002),dWPAdt(1002),stackA(2,2,4008)
      complex*16 WPB(1002),dWPBdt(1002),stackB(2,2,4008)
      real*8     WeA(1002),WeB(1002),Wg(1002)
      real*8     snpt,mass,dR,progress,WJ
      real*8     wptime,wpN,wpstep,random(1:2,2d7),rdm1000(1:2,1000)
      real*8     intensity,tc,tp,td,omegaL,Eg,energy,field
      real*8     rT,rdm,solarWidth
      real*8     time,PROB,expR,norm,location,tmp(1:6)

      !Parameters
      ImI        = (0.0d0,1.0d0)
      mass       = 918.0d0 !116586.0d0 !918.0d0
      NGRID      = 1002    !number of grid points in real space
      dR         = 0.04d0  !defined in the diagonalization of Wg
      J          = 1       !excited state J quantum number
      intensity  = 4.0d-18 !a.u. of sunlight intensity = 0.13 W/cm^2 
      tc         = 6.0d0/24.189d-3 !+ 19.0d0/24.189d-3
      tp         = 1.6d0 /24.189d-3   !1.6fs <- 0.015 a.u. of energy
      td         = 200.0d0/24.189d-3  !for pulse envelope
      solarWidth = 0.0175d0 !0.0175=150nm 
      omegaL     = 0.1d0    !456nm has period=1.52fs
      !electronic transition dipole function for 1sg->1su in H2+
      do i=1,NGRID
        edipole(i) = (real(i)*dR)/2.0d0
      enddo

      !######################################
      ! specify:
      ! 1 = random CW, 
      ! 0 = coherent ultrafast
      rdm    = 0.0d0

      !Make file name strings for later naming
      if(rdm==0.0d0)then
        filename = 'coht'
      else
        filename = 'rdm'
      endif
      !######################################
      
      ! Specify effective PES's for the two channels
      WeA = 0.0d0
      WeB = 0.0d0
      open(101,FILE='output/pes.output')
      do i=1,NGRID
        progress = real(i)*dR
        WJ       = real(J)*(real(J)+1.0d0)/(2.0d0*mass*progress**2)
        Wg(i)    = 0.1d0*(1.0d0-exp(-(progress-2.1d0)/1.5d0))**2.0d0-0.1d0
        !WeA(i)   = 0.1d0*exp(-(progress-3.3d0)/1.0d0) + 0.0d0 + WJ
        !WeB(i)   = 0.1d0*exp(-(progress-3.0d0)/1.2d0) + 0.005d0 + WJ

        !WeA(i) = 0.1d0*(1.0d0-exp(-(progress-4.5d0)/2.5d0))**2 ! Well 1
        !WeB(i) = 0.1d0*(1.0d0-exp(-(progress-5.0d0)/2.5d0))**2+0.01d0 !Well 2

        WeA(i) = 0.1d0*(1.0d0-exp(-(progress-5.0d0)/2.5d0))**2          !for heavy mass
        WeB(i) = 0.1d0*(1.0d0-exp(-(progress-5.01d0)/2.53d0))**2+0.01d0 !for heavy mass

        write(101,'(10(E22.15,3x))') progress,Wg(i),WeA(i),WeB(i)
      enddo
      close(101)
      !%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      !
      ! Specify initial state and its energy;
      ! Quantum number nu = number of nodes
      !
      !%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      nu = 5

      PSI_G  = 0.0d0
      open(101,FILE='input/eigenvectors.txt')
      do i=1,500
         read(101,*) (dummy,k=1,nu+1),PSI_G(i)
         !read(101,*) dummy
         progress  = real(i)*dR
         PSI_G(i)  = PSI_G(i)*edipole(i)*progress
      enddo
      close(101)

      open(101,FILE='input/eigenvalues.txt')
      do i=1,nu+1
         read(101,*) dummy,Eg
      enddo
      close(101)

      !%%%%%%%%%%%%%%%%%%%%%%%%%%
      !
      !       Propagation
      !
      !%%%%%%%%%%%%%%%%%%%%%%%%%%

      ! Propagation paramaters
      wptime = 300.0d0/0.024d0 ! fs/a.u.
      wpN    = 1.0d6 !1.0d5 is good
      wpstep = wptime/wpN !time in a.u. of each propagation step
      Nout   = 200 !number of output snapshots

      !Generate Random Parameters
      call random_seed()!restart generator
      call random_number(rdm1000)
      !rT = number of steps in which no jump occurs
      rT = (7.0d0 /0.024d0) / real(wpstep)
      do i=0,int(wpN/rT)-1
        do k=1,int(rT)
          random(1,i*int(rT)+k) = rdm1000(1,i)
          random(2,i*int(rT)+k) = rdm1000(2,i)
        enddo
      enddo
      do i=1,wpN
        random(1,i) = rdm*3.14d0    *(2.0d0*random(1,i)-1.0d0)
        random(2,i) = rdm*solarWidth*(2.0d0*random(2,i)-1.0d0)
      enddo

      ! Calculate the field shape normalization factor
      energy = 0.0d0
      do i=1,1d4
        if(rdm==1.0d0)then
          progress = real(i) * td/1d4
          field    = envelope(progress/td)
        else
          progress = real(i) * (tc+8.0d0*tp)/1d4
          field    = exp(-(progress-tc)**2/(2.0d0*tp**2))
        endif
        k        = int(progress/wpstep)
        field    = field*cos((omegaL+random(2,k))*progress+random(1,k))
        energy   = energy + (field**2) * progress/real(i)
      enddo
      energy = sqrt(energy)

      !output the pulse function
      open(101,FILE='output/pulse-'//trim(filename)//'.output')
      do i=1,5000
        if(rdm==1.0d0)then
          progress = real(i) * td/5000.0d0
          field    = envelope(progress/td)
        else
          progress = real(i) * (tc+4.0d0*tp)/5000.0d0
          field    = exp(-(progress-tc)**2/(2.0d0*tp**2))
        endif
        k        = int(progress/wpstep)
        field    = field*cos((omegaL+random(2,k))*progress+random(1,k))
        field    = field*sqrt(intensity)/energy
        write(101,*) progress*0.024d0, field
      enddo
      close(101)

      ! Wave Packet Propagation with central-point method
      ! WP_N = WP_N-2 + 2dt*dWPdt_N-1 
      ! Use a 'stack' to record two previous propagation points
      ! ----------------------------
      ! |     WP_N-2  |    WP_N-1  |     WP_N
      ! |  dWPdt_N-2  | dWPdt_N-1  |  dWPdt_N
      ! ----------------------------
      WPA    = 0.0d0
      dWPAdt = 0.0d0
      WPB    = 0.0d0
      dWPBdt = 0.0d0
      stackA = 0.0d0
      stackB = 0.0d0
      open(101,FILE='output/wp-'//trim(filename)//'.output')
      open(102,FILE='output/correlation-'//trim(filename)//'.output')
      do i=2,int(wpN)
        progress = real(i)*wpstep
        if(rdm==1.0d0)then
          pulse  = envelope(progress/td)
        else
          pulse  = exp(-(progress-tc)**2/(2.0d0*tp**2))
        endif
        pulse    = pulse*cos((omegaL+random(2,i))*progress+random(1,i))
        pulse    = pulse*exp(-ImI*Eg*progress)
        pulse    = pulse*sqrt(intensity)/energy

        do m=1,NGRID
         WPA(m) = stackA(1,1,m) + 2.0d0*wpstep*stackA(2,2,m)
         WPB(m) = stackB(1,1,m) + 2.0d0*wpstep*stackB(2,2,m)
        enddo

        dWPAdt = - ImI*HePSI(dR,mass,WeA,WPA) + PSI_G*pulse
        dWPBdt = - ImI*HePSI(dR,mass,WeB,WPB) + PSI_G*pulse

        do m=1,NGRID
         stackA(1,1,m) = stackA(1,2,m)
         stackA(2,1,m) = stackA(2,2,m)
         stackA(1,2,m) = WPA(m)
         stackA(2,2,m) = dWPAdt(m) 

         stackB(1,1,m) = stackB(1,2,m)
         stackB(2,1,m) = stackB(2,2,m)
         stackB(1,2,m) = WPB(m)
         stackB(2,2,m) = dWPBdt(m) 
        enddo

        !output snapshots of two wave packets
        do l=1,Nout
        if(i==int(real(l)*wpN/real(Nout)))then
           snpt  = real(l)*(wptime*0.024189d0)/real(Nout)
           rho   = 0.0d0
           do k=1,NGRID
             tmp(1) = real(k)*dR
             tmp(2) = snpt
             tmp(3) = real(WPA(k))
             tmp(4) = aimag(WPA(k))
             tmp(5) = real(WPB(k))
             tmp(6) = aimag(WPB(k))
             do m=1,6!for numerical convenience
              if(abs(tmp(m)).le.0.2d-98)then
                tmp(m) = 0.0d0
              endif
             enddo
             rho(1,1) = rho(1,1) + abs(WPA(k))**2*dR
             rho(2,2) = rho(2,2) + abs(WPB(k))**2*dR
             rho(2,1) = rho(2,1) + conjg(WPA(k))*WPB(k)*dR
             !write(101,'(6(E22.15,3x))') (tmp(loop),loop=1,6)
           enddo
           !rho(2,1) = rho(2,1)/(rho(1,1)+rho(2,2))
           !write(101,*) ''! two empty line to separate
           !write(101,*) ''! gnuplot data blocks
           write(102,'(10(E22.15,3x))') snpt,abs(rho(2,1))/(abs(rho(1,1))+abs(rho(2,2)))
           print *,l,'/',Nout,'done'
        endif
        enddo

      enddo
      close(101)
      close(102)

      ! %%%%%%%%%% FUNCTIONS %%%%%%%%%%
      CONTAINS
      !%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      function HePSI(dR,mass,We,PSI)
      implicit none
      integer i
      complex*16,dimension(1002) :: HePSI
      complex*16 PSI(1002),KE_PSI
      real*8     We(1002),dR,mass

      HePSI(1) = 0.0d0
      do i=2,1002
        KE_PSI   = (PSI(i-1)-2.0d0*PSI(i)+PSI(i+1))/(dR**2)
        KE_PSI   = (-1.0d0/(2.0d0*mass)) * KE_PSI
        HePSI(i) = KE_PSI + We(i)*PSI(i)
      enddo

      end function
      !%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      !pulse shape with maximum value 1 in [0:1]
      real*8 function envelope(q)
      implicit none
      real*8 q

      if(q.ge.0.0d0.and.q.le.1.0d0)then
        envelope = sin(3.1415926d0*q)**(0.1d0)
      else
        envelope = 0.0d0
      endif
      end function
      !%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      end
