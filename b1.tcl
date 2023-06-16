# 1. Simulate a three nodes point – to – point network with duplex links between them. Set the queue size and vary the bandwidth and find the number of packets dropped.

set ns [new Simulator]

set tf [open out.tr w]
$ns trace-all $tf
set nf [open out.nam w]
$ns namtrace-all $nf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n2 10Mb 300ms DropTail
$ns duplex-link $n1 $n2 10Mb 300ms DropTail
$ns duplex-link $n2 $n3 1Mb 300ms DropTail

$ns queue-limit $n0 $n2 10
$ns queue-limit $n1 $n2 10
$ns queue-limit $n2 $n3 10

set udp0 [new Agent/UDP]
set udp1 [new Agent/UDP]
$ns attach-agent $n0 $udp0
$ns attach-agent $n1 $udp1

set cbr0 [new Application/Traffic/CBR]
set cbr1 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
$cbr1 attach-agent $udp1

set null3 [new Agent/Null]
$ns attach-agent $n3 $null3

$ns connect $udp0 $null3
$ns connect $udp1 $null3

$cbr0 set packetSize_ 500Mb
$cbr1 set packetSize_ 500Mb
$cbr0 set interval_ 0.005
$cbr1 set interval_ 0.005

proc finish {} {
	global ns nf tf
	$ns flush-trace
	exec nam out.nam &
	close $tf 
	close $nf
	
	set count 0
	set tf [open out.tr r]
	while {[gets $tf line] != -1} {
		# d is event in the trace file which denotes dropped packets 
		if { [string match "d*" $line] } {
			set count [expr $count + 1]
		}
	}
	puts "Number of packets dropped: $count"
	exit 0
}

$ns at 0.01 "$cbr0 start"
$ns at 0.01 "$cbr1 start"
$ns at 5.0 "finish"
$ns run
