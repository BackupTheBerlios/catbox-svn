#!/usr/bin/perl
# tcp-server-st.pl -- Ein Single-threaded-TCP-Server

use strict;
use IO::Socket;

# --------------- Konfiguration --------------------

use constant MYPORT => 1860;
# use constant PASSWD => "lassmichrein";
use constant PASSWD => "";

# --------------------------------------------------

my $hostname = "/bin/hostname";
my $dfcmd    = "/bin/df";
my $ifconfig = "/sbin/ifconfig";
my $netstat  = "/bin/netstat";
my $top      = "/usr/bin/top -b -n 1";
#my $netdev   = "/bin/cat /proc/net/dev";
my $devices  = "/bin/cat /proc/bus/usb/devices";
my $dmesg    = "/bin/dmesg";
my $mount    = "/bin/mount";
my $uname    = "/bin/uname";
my $grep     = "/bin/grep";

# --------------------------------------------------

my $sock = '';
my $client = 0;
my $line = '';
my $erg = '';

$sock = new IO::Socket::INET(LocalPort => MYPORT,
		             Reuse     => 1,
		             Listen    => 5)
    or die "can't create local socket: $@\n";
print "Accepting connections on Port ", MYPORT, "...\n";

while ($client = $sock->accept()) 
  {
  # Eine Verbindung ist eingetroffen.
  print "Accepted connection from ",
        $client->peerhost(), ":", $client->peerport(), "\n";
  print $client "Observer 0.1 Nice to meet you\n";
  print $client "AUTH\n";
  $line = <$client>;
  chomp($line); $line =~ s/\r//;

  # Passwort check
  unless ($line eq PASSWD)
    {
    print $client "FAIL\n";
    $client->close() if defined $client;
    next;
    }
  print $client "OK\n";

  # Jetzt geht's los
  $line = <$client>;
  chomp($line); $line =~ s/\r//;
  if ($line eq 'STAT')  
    {
    &bootinfo;
    &netinfo("s");
    }
  elsif ($line eq 'DYNA')
    {
    &fileinfo;
    &netinfo("d");
    &cpuinfo;
    &usbinfo;
    }
  print $client "FINISH\n";
  $client->close() if defined $client;
  }


sub bootinfo
  {
  my $erg;
  my $line;
  $erg = `$hostname`;
  print $client "hostname: $erg\n";
  $erg = `$uname -r`;
  chomp($erg);
  $erg =~ s/(^[0-9\.]*).*/$1/;
  $erg = `$uname -o` . $erg;
  print $client "os: $erg\n";
  open DAT,"$dmesg |";
  while ($line = <DAT>)
    {
    print $client "dmesg_" . $line;
    }
  close(DAT);
  }


sub fileinfo
  {
  my $line = '';
  # Platten
  open DAT,"$dfcmd |";
  while ($line = <DAT>)
    {
    print $client "df: $line" if ($line =~ /^\/dev/);
    }
  close(DAT);
  open DAT,"$mount |";
  while ($line = <DAT>)
    {
    print $client "mount: " . $line;
    }
  close(DAT);
  }

    
sub usbinfo
  {
  # Info ueber USB-Geräte
  my $line = '';
  my $first = 1;

  open DAT,"$devices |";
  while ($line = <DAT>)
    {
    if ($line =~ /^T:/)
      {
      print $client "\n" unless($first);
      print $client "usb:";
      $first = 0;
      }
    if ($line =~ /^S:/)
      {
      $line =~ s/^S: //; chomp($line);
      print $client " $line";
      }
    }
  print $client "\n";
  close(DAT);
  }

sub cpuinfo
  {  
  # "/usr/bin/top -b -n 1" -> top only ONE fingerprint (-n 1) and 
  # in batch mode (-b) (without funny formatting)
  my $line = '';

  open DAT,"$top |";
  while ($line = <DAT>)
    { # cut out only the lines with Mem and Cpu info
    print $client "cpu: $line" if $line =~ /Mem|Cpu|Task|Swap/;
    }
  close(DAT);
  }

sub netinfo # (static/dunamic)
  {
  my $erg = '';
  my $Typ = shift;

  if ($Typ eq "s")
    {
	# Statische Netzwerkinfo:
	# mit Hilfe von "ifconfig": Erkennen der NSK mit dazugehöriger MAC und IP-Nummer
	$erg = `$ifconfig`;
	print $client "ifconfig: $erg\n";
    }
  else
    {
	# Dynamische Netzwerkinfos:
	# mit Hilfe von netstat Ausgabe der offenen Ports am Server
	$erg = `$netstat -i`;
	print $client "netstat_i: $erg\n";
	$erg = `$netstat -s`;
	print $client "netstat_s: $erg\n";
#	$erg = `$netdev`;
#	print $client "net-dev: $erg\n";
    }
  }
