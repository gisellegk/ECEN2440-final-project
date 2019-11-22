*version 9.2 1071864586
u 147
U? 2
C? 3
V? 2
R? 4
? 3
@libraries
@analysis
.TRAN 1 0 0 0
+0 1ns
+1 1000ns
.LIB D:\Data\Spring Work\ncv1117\All NCP1117 PSpice Models\NCP1117 Model Library.lib
@targets
@attributes
@translators
a 0 u 13 0 0 0 hln 100 PCBOARDS=PCB
a 0 u 13 0 0 0 hln 100 PSPICE=PSPICE
a 0 u 13 0 0 0 hln 100 XILINX=XILINX
@setup
unconnectedPins 0
connectViaLabel 0
connectViaLocalLabels 0
NoStim4ExtIFPortsWarnings 1
AutoGenStim4ExtIFPorts 1
@index
pageloc 1 0 3621 
@status
n 0 105:02:30:10:08:32;1112195312 e 
s 0 105:02:30:10:08:36;1112195316 e 
c 105:02:30:10:09:02;1112195342
*page 1 0 1520 970 iB
@ports
port 5 GND_EARTH 170 310 h
@parts
part 3 C 230 260 v
a 0 sp 0 0 0 10 hlb 100 PART=C
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=C1
a 0 ap 9 0 15 0 hln 100 REFDES=C1
a 0 u 13 0 15 33 hln 100 VALUE=10u
part 4 C 470 260 v
a 0 sp 0 0 0 10 hlb 100 PART=C
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 u 13 0 15 33 hln 100 VALUE=10u
a 0 a 0:13 0 0 0 hln 100 PKGREF=C2
a 0 ap 9 0 15 0 hln 100 REFDES=C2
part 6 VDC 170 230 h
a 1 ap 9 0 26 17 hcn 100 REFDES=V1
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 0 a 0:13 0 0 0 hln 100 PKGREF=V1
a 1 u 13 0 -11 18 hcn 100 DC=3.3V
part 2 ncp1117_adj1-x 310 220 h
a 0 sp 11 0 40 10 hcn 100 PART=ncp1117_adj1-x
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=U1
a 1 ap 9 0 16 -2 hcn 100 REFDES=U1
part 102 r 420 270 v
a 0 u 13 0 15 29 hln 100 VALUE=100
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=R1
a 0 xp 9 0 15 0 hln 100 REFDES=R1
part 103 r 350 310 v
a 0 u 13 0 15 35 hln 100 VALUE=2.83
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=R2
a 0 xp 9 0 15 0 hln 100 REFDES=R2
part 55 r 490 220 h
a 0 u 13 0 17 29 hln 100 VALUE=130
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=Rload
a 0 xp 9 0 25 0 hln 100 REFDES=Rload
part 1 titleblk 1520 970 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=B
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 300 95 hrn 100 PAGENO=1
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
part 136 nodeMarker 420 220 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=C2:2
a 0 a 0 0 4 22 hlb 100 LABEL=1
part 137 iMarker 490 220 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 a 0 0 6 20 hlb 100 LABEL=2
@conn
w 8
a 0 up 0:33 0 0 0 hln 100 V=
s 230 220 310 220 76
a 0 up 33 0 270 219 hct 100 V=
s 230 230 230 220 73
s 170 220 230 220 9
s 170 220 170 230 96
w 107
a 0 up 0:33 0 0 0 hln 100 V=
s 350 250 350 270 108
s 350 270 420 270 110
a 0 up 33 0 385 269 hct 100 V=
w 134
a 0 up 0:33 0 0 0 hln 100 V=
s 470 310 470 260 36
s 350 310 470 310 124
s 230 310 350 310 104
a 0 up 33 0 290 309 hct 100 V=
s 230 310 230 260 78
s 170 310 230 310 14
s 170 310 170 270 113
s 470 310 540 310 70
s 540 220 540 310 64
s 530 220 540 220 62
w 19
a 0 up 0:33 0 0 0 hln 100 V=
s 470 230 470 220 68
s 420 220 390 220 131
s 420 230 420 220 129
s 470 220 420 220 141
a 0 up 33 0 445 219 hct 100 V=
s 470 220 490 220 142
@junction
j 310 220
+ p 2 IN
+ w 8
j 390 220
+ p 2 OUT
+ w 19
j 470 230
+ p 4 2
+ w 19
j 230 230
+ p 3 2
+ w 8
j 230 220
+ w 8
+ w 8
j 170 230
+ p 6 +
+ w 8
j 230 260
+ p 3 1
+ w 134
j 470 260
+ p 4 1
+ w 134
j 170 270
+ p 6 -
+ w 134
j 170 310
+ s 5
+ w 134
j 230 310
+ w 134
+ w 134
j 350 250
+ p 2 GND
+ w 107
j 420 270
+ p 102 1
+ w 107
j 420 230
+ p 102 2
+ w 19
j 420 220
+ w 19
+ w 19
j 350 310
+ p 103 1
+ w 134
j 350 270
+ p 103 2
+ w 107
j 470 220
+ w 19
+ w 19
j 470 310
+ w 134
+ w 134
j 420 220
+ p 136 pin1
+ w 19
j 530 220
+ p 55 2
+ w 134
j 490 220
+ p 55 1
+ w 19
j 490 220
+ p 137 pin1
+ p 55 1
j 490 220
+ p 137 pin1
+ w 19
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=B
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
t 145 t 5 150 126 320 150 0 63
NCP1117 - Adjustable Voltage Regulator
VIN = 3.3V; VOUT = 1.3V
t 146 t 5 150 366 370 400 0 99
Refer to Figure 21 in the NCP1117 data sheet.
http://www.onsemi.com/pub/Collateral/NCP1117-D.PDF

