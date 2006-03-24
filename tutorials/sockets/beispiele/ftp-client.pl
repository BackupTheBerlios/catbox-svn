#!/usr/local/bin/perl -w
# Verwendung: ftp-client.pl Datei

use Net::FTP;

# ----- CONFIGURATION -------------------------------------------
use constant USER => 'anonymous';
use constant PASS => 'user@host.domain.tld';
# ----- ab hier nichts mehr aendern -----------------------------

while (<>) 
  {
  chomp;   # Abschliessendes Newline entfernen

  # Nur FTP-URLs der Form: hostname:/path akzeptieren
  next unless m/(.+?):\/(.+)/;
  ($host, $path) = ($1, $2);

  # Erzeuge neues Net::FTP-Objekt mit dem Ziel $host
  my $ftp = Net::FTP->new($host);
  unless (defined $ftp) 
    { 
    warn "Can't create Net::FTP Object to $host: $@\n"; 
    next;
    }

  # Beim FTP-Server einloggen
  unless (defined ($ftp->login(USER, PASS))) 
    {
    warn "can't login to $host\n";
    next;
    }
	
  # Binary-Modus, damit Dateien unveraendert bleiben
  $ftp->binary();
	
  # Hole Datei /$path
  # und speichere sie lokal unter dem gleichen Namen (ohne Pad)
  unless (defined ($ftp->get("/$path", basename($path)))) 
    {
    warn "can't get file /$path\n"; 
    next;
    }

  # Aus dem FTP-Server ausloggen.
  $ftp->quit();
  }

sub basename 
  {
  my($name) = shift;
  $name =~ s/^.*\///;
  }
