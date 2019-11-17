*version 9.2 1039275388
u 67
U? 2
C? 3
R? 2
V? 2
? 3
@libraries
@analysis
.TRAN 1 0 0 0
+0 1ns
+1 1000ns
.LIB D:\Data\Spring Work\ncv1117\All NCP1117 PSpice Models\Final 1117 test\All NCP1117 Models.lib
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
pageloc 1 0 2763 
@status
n 0 105:02:30:10:53:45;1112198025 e 
s 2833 105:02:30:10:53:48;1112198028 e 
*page 1 0 1520 970 iB
@ports
port 41 GND_EARTH 230 280 h
@parts
part 2 ncp1117_50-x 340 240 h
a 0 sp 11 0 40 10 hcn 100 PART=ncp1117_50-x
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=U1
a 1 ap 9 0 16 -2 hcn 100 REFDES=U1
part 23 VDC 230 240 h
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 0 a 0:13 0 0 0 hln 100 PKGREF=V1
a 1 ap 9 0 24 7 hcn 100 REFDES=V1
a 1 u 13 0 -11 18 hcn 100 DC=7.0V
part 3 C 290 270 v
a 0 sp 0 0 0 10 hlb 100 PART=C
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=C1
a 0 ap 9 0 15 0 hln 100 REFDES=C1
a 0 u 13 0 15 33 hln 100 VALUE=10u
part 4 C 460 270 v
a 0 sp 0 0 0 10 hlb 100 PART=C
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 u 13 0 15 33 hln 100 VALUE=10u
a 0 a 0:13 0 0 0 hln 100 PKGREF=C2
a 0 ap 9 0 15 0 hln 100 REFDES=C2
part 12 r 530 240 h
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=Rload
a 0 xp 9 0 25 0 hln 100 REFDES=Rload
a 0 u 13 0 25 25 hln 100 VALUE=500
part 1 titleblk 1520 970 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=B
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 300 95 hrn 100 PAGENO=1
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
part 46 iMarker 530 240 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 a 0 0 6 20 hlb 100 LABEL=2
part 42 nodeMarker 460 240 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=C2:2
a 0 a 0 0 4 22 hlb 100 LABEL=1
@conn
w 47
a 0 up 0:33 0 0 0 hln 100 V=
s 570 280 570 240 17
s 290 280 230 280 43
s 290 280 290 270 31
s 290 280 380 280 7
s 380 280 380 270 32
s 380 280 460 280 9
a 0 up 33 0 515 279 hct 100 V=
s 460 280 570 280 62
s 460 280 460 270 30
w 6
a 0 up 0:33 0 0 0 hln 100 V=
s 290 240 230 240 24
a 0 up 33 0 260 239 hct 100 V=
s 290 240 340 240 5
w 53
a 0 up 0:33 0 0 0 hln 100 V=
s 530 240 460 240 63
a 0 up 33 0 505 239 hct 100 V=
s 460 240 420 240 66
@junction
j 230 280
+ p 23 -
+ s 41
j 460 240
+ p 4 2
+ w 53
j 570 240
+ p 12 2
+ w 47
j 290 280
+ w 47
+ w 47
j 230 280
+ p 23 -
+ w 47
j 230 280
+ s 41
+ w 47
j 290 270
+ p 3 1
+ w 47
j 380 270
+ p 2 GND
+ w 47
j 380 280
+ w 47
+ w 47
j 460 270
+ p 4 1
+ w 47
j 460 280
+ w 47
+ w 47
j 530 240
+ p 12 1
+ w 53
j 420 240
+ p 2 OUT
+ w 53
j 230 240
+ p 23 +
+ w 6
j 290 240
+ p 3 2
+ w 6
j 340 240
+ p 2 IN
+ w 6
j 530 240
+ p 46 pin1
+ p 12 1
j 530 240
+ p 46 pin1
+ w 53
j 460 240
+ p 42 pin1
+ p 4 2
j 460 240
+ p 42 pin1
+ w 53
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=B
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
t 49 t 5 240 136 390 160 0 33
NCP1117 - Fixed Voltage Regulator
t 50 t 5 240 346 470 390 0 86
Refer to the NCP1117 data sheet.
http://www.onsemi.com/pub/Collateral/NCP1117-D.PDF

