.ALIASES
R_R1            R1(1=ADJ 2=0 ) CN @BD00C0AWFP.9_OutputVoltageCTLVoltage(sch_1):INS17406@ANALOG.R.Normal(chips)
R_R2            R2(1=VOUT 2=ADJ ) CN @BD00C0AWFP.9_OutputVoltageCTLVoltage(sch_1):INS17214@ANALOG.R.Normal(chips)
X_U1            U1(CTL=CTL VCC=VCC NC1=0 VO=VOUT ADJ=ADJ GND=0 ) CN
+@BD00C0AWFP.9_OutputVoltageCTLVoltage(sch_1):INS17078@BDXXC0AXFP.BD00C0AWFP.Normal(chips)
V_VCC           VCC(+=VCC -=0 ) CN @BD00C0AWFP.9_OutputVoltageCTLVoltage(sch_1):INS17262@SOURCE.VSRC.Normal(chips)
V_VCTL          VCTL(+=CTL -=0 ) CN @BD00C0AWFP.9_OutputVoltageCTLVoltage(sch_1):INS17234@SOURCE.VSRC.Normal(chips)
C_CIN           CIN(1=0 2=N17350 ) CN @BD00C0AWFP.9_OutputVoltageCTLVoltage(sch_1):INS17374@ANALOG.C.Normal(chips)
R_RESR1          RESR1(1=VCC 2=N17350 ) CN @BD00C0AWFP.9_OutputVoltageCTLVoltage(sch_1):INS17290@ANALOG.R.Normal(chips)
C_COUT          COUT(1=0 2=N17356 ) CN @BD00C0AWFP.9_OutputVoltageCTLVoltage(sch_1):INS17390@ANALOG.C.Normal(chips)
R_RESR2          RESR2(1=VOUT 2=N17356 ) CN @BD00C0AWFP.9_OutputVoltageCTLVoltage(sch_1):INS17310@ANALOG.R.Normal(chips)
_    _(ADJ=ADJ)
_    _(CTL=CTL)
_    _(VCC=VCC)
_    _(VOUT=VOUT)
.ENDALIASES
