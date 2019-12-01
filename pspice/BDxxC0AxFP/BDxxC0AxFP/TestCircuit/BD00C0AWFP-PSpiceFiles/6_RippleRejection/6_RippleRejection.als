.ALIASES
R_RL            RL(1=VOUT 2=0 ) CN @BD00C0AWFP.6_RippleRejection(sch_1):INS18282@ANALOG.R.Normal(chips)
R_RESR1          RESR1(1=VCC 2=N18052 ) CN @BD00C0AWFP.6_RippleRejection(sch_1):INS17976@ANALOG.R.Normal(chips)
X_U1            U1(CTL=CTL VCC=VCC NC1=0 VO=VOUT ADJ=ADJ GND=0 ) CN
+@BD00C0AWFP.6_RippleRejection(sch_1):INS17764@BDXXC0AXFP.BD00C0AWFP.Normal(chips)
R_RESR2          RESR2(1=VOUT 2=N18058 ) CN @BD00C0AWFP.6_RippleRejection(sch_1):INS17996@ANALOG.R.Normal(chips)
R_R2            R2(1=VOUT 2=ADJ ) CN @BD00C0AWFP.6_RippleRejection(sch_1):INS17900@ANALOG.R.Normal(chips)
V_VCC           VCC(+=VCC -=0 ) CN @BD00C0AWFP.6_RippleRejection(sch_1):INS17948@SOURCE.VSRC.Normal(chips)
R_R1            R1(1=ADJ 2=0 ) CN @BD00C0AWFP.6_RippleRejection(sch_1):INS18108@ANALOG.R.Normal(chips)
C_COUT          COUT(1=0 2=N18058 ) CN @BD00C0AWFP.6_RippleRejection(sch_1):INS18092@ANALOG.C.Normal(chips)
C_CIN           CIN(1=0 2=N18052 ) CN @BD00C0AWFP.6_RippleRejection(sch_1):INS18076@ANALOG.C.Normal(chips)
V_VCTL          VCTL(+=CTL -=0 ) CN @BD00C0AWFP.6_RippleRejection(sch_1):INS17920@SOURCE.VSRC.Normal(chips)
_    _(ADJ=ADJ)
_    _(CTL=CTL)
_    _(VCC=VCC)
_    _(VOUT=VOUT)
.ENDALIASES
