#!/usr/bin/perl
# Scipt baut eine Verbindung zum ausgew&auml;hlten "Zeitserver" auf
# und liefert dann die genaue Uhrzeit an den Client

use IO::Socket;
use strict;

use constant CLPORT => 1300;
use constant SVPORT => 35;
use constant KORR => 2208988800;

my $hostname = "mail.ee.fhm.edu";

my $serversock = new IO::Socket::INET (
                   LocalPort => CLPORT,
                   Listen    => 5,
                   Proto     => 'tcp',
                   Reuse     => 1)
     or die "can't create local socket: $@\n";

# In der Schleife auf eingehende Verbindungen warten... 
print "Accepting connections on Port ", CLPORT, "...\n";

while (my $clientsock = $serversock->accept() ) 
  {
  my $cur_time = &get_time;
  print $clientsock "$cur_time\n";
  $clientsock->close() if defined $clientsock;
  }

# Zeit vom anderen Server holen
sub get_time
  {
  my ($binarytime, $servertime);
  my $ts_sock = new IO::Socket::INET (
                      PeerAddr => $hostname,
                      PeerPort => 37,
                      Proto    => 'tcp')
       or die "can't create local socket: $@\n";

  read($ts_sock,$binarytime,4);
  $ts_sock->close();
  $servertime = unpack('N',$binarytime);
  $servertime = localtime($servertime - KORR);
  return "$servertime";
  }

