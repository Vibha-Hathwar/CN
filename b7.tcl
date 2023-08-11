set ns [new Simulator]
set tf [open out.tr w]
$ns trace-all $tf
set nf [open out.nam w]
$ns namtrace-all-wireless $nf 200 200
set topo [new Topography]
$topo load_flatgrid 200 200
$ns node-config -adhocRouting DSDV \
-llType LL \
-macType Mac/802_11 \
-ifqType Queue/DropTail \
-ifqLen 50 \
-phyType Phy/WirelessPhy \
-channelType Channel/WirelessChannel \
-propType Propagation/TwoRayGround \
-antType Antenna/OmniAntenna \
-topoInstance $topo \
-agentTrace ON \
-routerTrace ON \
-macTrace ON
create-god 3
set n0 [$ns node]
set n1 [$ns node]

$n0 label "tcp0"
$n1 label "sink1"

$n0 set X_ 10
$n0 set Y_ 100
$n0 set Z_ 0

$n1 set X_ 100
$n1 set Y_ 100
$n1 set Z_ 0

$ns at 0.0 "$n0 setdest 10 100 15"
$ns at 0.0 "$n1 setdest 100 100 15"

set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

$ns connect $tcp0 $sink1

$ns at 1 "$ftp0 start"

proc finish { } {
global ns nf tf
$ns flush-trace
exec nam out.nam &
close $tf

set ctr 0
set thr 0
set fid [open out.tr r]

while {[gets $fid line] != -1} {
if {[string match "r*_1_*AGT*" $line]} {
set ctr [expr $ctr +1]
}
}
set thr [expr $ctr/5]
puts "\nThroughput : $thr"
exit 0
}
$ns at 10 "finish"
$ns run
