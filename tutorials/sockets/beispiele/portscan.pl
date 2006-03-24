#!/usr/bin/perl -w

use IO::Socket;

use strict;     

my $pinghost = '';
$|=1;

foreach $pinghost (@ARGV)
  {
  &port_scan($pinghost, 1, 1024);
  }
exit;   


sub port_scan  # ($hostip, $lowport, $highport)
  {
  my $port = 0;
  my $iaddr = 0;
  my $paddr = 0;
  my $connect_time = 1;
  my $protocol_name = "tcp";
  my $protocol_id = getprotobyname($protocol_name);
  my $hostip = shift;
  my $lowport = shift;
  my $highport = shift;


  print "Portscan von $hostip.\n";
  for ($port = $lowport; $port <= $highport; $port++) 
    {
    $SIG{"ALRM"} = sub { close(SOCKET); };
    alarm $connect_time;
  
    socket(SOCKET, PF_INET, SOCK_STREAM, $protocol_id);

    $iaddr  = inet_aton($hostip);
    $paddr  = sockaddr_in($port, $iaddr);   
        
    print "  Port $port offen.\n" if (connect(SOCKET, $paddr));
    close(SOCKET); 
    }
  }
