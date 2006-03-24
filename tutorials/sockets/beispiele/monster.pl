#!/usr/bin/perl
# Keks-Monster

use strict;
use IO::Socket;

use constant MYPORT => 2300;
my $sock = '';
my $client = '';

$sock = new IO::Socket::INET(LocalPort => MYPORT,
		             Reuse     => 1,
		             Listen    => 5)
    or die "can't create local socket: $@\n";

$SIG{'CHLD'} = sub { wait(); };    # Zombies verhindern

print "Accepting connections on Port ", MYPORT, "...\n";
while ($client = $sock->accept()) 
  {
  # Verbindung ist aufgebaut
  print "Accepted connection from ",
        $client->peerhost(), ":", $client->peerport(), "\n";

  # Erzeugen eines Kindprozesses und Uebergabe an $client.
  if (fork() == 0) # Kindprozess 
    {
    $sock->close; # not needed in child
    # Das Monster in Aktion
    print $client "Ich will KEKSE!\n";
    while (<$client>) 
      {
      chomp;
      if ($_ =~ /KEKSE/)
        {
        print $client "\nMampf, Mampf....\n\n";
        $client->close;
        exit 0;
        }
      print $client "Ich will KEKSE!\n";
      }
    }
   $client->close; # not needed in parent
   }
