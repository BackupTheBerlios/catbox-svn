#!/usr/bin/perl -w

use IO::Socket;
use Net::Ping;

use strict;     

#########################################################################
# Netzwerk-Ueberwachungstool, das ein C-Netz nach Rechnern durchsucht
# -------------------------------------------------------------------
# Dieses Programm 'pingt' alle moeglichen Rechner eines C-Netzes an
# (von Hostnummer 1 - 253; 254 wird ausgelassen, da bei uns immer Gateway)
#
# Nicht erreichbare Hosts spielen keine Rolle. Fuer erreichbare Hosts
# wird der Name abgefragt. Hat er keinen Namen (d. h. keinen Nameserver-
# Eintrag), wird er als 'verdaechtig' gemeldet.
#
# Nachden das ganze etwas dauert (Timeout bei unbenutzten Nummern),
# laesst man den Output entweder in eine Datei laufen oder per Mail
# versenden und startet das Ganze per cron-Job.
#
# Wer will kann sich natuerlich auch alle aktiven Rechner ausgeben 
# lassen.
#
# Die zu scannenden Netze werden auf der Kommandozeile angegeben, 
# z. B.: pinger '10.10.10' '10.10.11' '192.168.33'
#
# Optionen:
# -a    Alle aktiven Rechner auflisten
# -p    Portscan verdaechtiger Rechner
#
#########################################################################

my @networks = ();
my $all = 0;
my $portscan = 0;
my %opt = ();
my $network = '';
my $pinghost = '';
my $hostname = '';
my $ret = 0;
my $count = 0;

$|=1;

# Parameter bearbeiten
for ($count = 0; $count <= $#ARGV; $count++)
  {
  $ret = $ARGV[$count];
  if ($ret eq '-a')
    { $all = 1; }
  elsif ($ret eq '-p')
    { $portscan = 1; }
  elsif ($ret eq '-ap' || $ret eq '-pa')
    { $all = 1; $portscan = 1; }
  else
    { push @networks, $ret; }
  }

foreach $network (@networks)
  {
  print "Scanning Network $network.0 \n";
  # Achtung: die Hostadresse 254 wird nicht getestet (Gateway)
  for ($count = 1; $count < 254; $count++)
    {
    $pinghost = $network . "." . $count;
    $hostname = &get_host($pinghost);
    $ret = &pinger($pinghost);
    if ($ret == 1)
      {
      if ($hostname eq '')
        { 
        print "   $pinghost ($hostname) verdaechtig!\n"; 
        if ($portscan)
          { &port_scan($pinghost, 1, 1024); }
        }
      elsif ($all)
        { print "   $pinghost ($hostname)\n"; }
      }
    }
  }
exit;   

sub pinger # (Host)
  {
  # Parameter: Host
  my $host = shift;         # zu pingender Host
  my $retval = 0;           # Ergebnis: 0 nicht erreicht, 1 erreicht, 2 Fehler
  # Neues Net-Ping Objekt
  my $p = Net::Ping->new('icmp');
  unless (defined $p) { die "*** can't create Net::Ping object $!";}

  # Exceptions auffangen
  eval 
    {
    $retval = 1 if ($p->ping($host)); 
    if ($@) 
      {
      print "*** Ping failed\n*** $@\n";
      $retval = 2;
      }
    $p->close;
    undef ($p);
    sleep(1);       # avoid network flooding
    return $retval;
    }
  }

sub get_host 
  {
  # Arg 1: IP-Adresse als String
  # Return: Host-Name als String
  my $iaddr = shift;
  my $host = '';
  # String in numerisches Format wandeln
  $iaddr = inet_aton($iaddr);
  $host = gethostbyaddr($iaddr,AF_INET);
  $host = '' unless (defined($host));
  return $host;
  }

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


  print "     Portscan von $hostip.\n";
  for ($port = $lowport; $port <= $highport; $port++) 
    {
    $SIG{"ALRM"} = sub { close(SOCKET); };
    alarm $connect_time;
  
    socket(SOCKET, PF_INET, SOCK_STREAM, $protocol_id);

    $iaddr  = inet_aton($hostip);
    $paddr  = sockaddr_in($port, $iaddr);   
        
    print "     Port $port offen.\n" if (connect(SOCKET, $paddr));
    close(SOCKET); 
    }
  }
