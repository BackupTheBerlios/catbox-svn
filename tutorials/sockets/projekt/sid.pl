#!/usr/bin/perl
use strict;


# Session ID erstellen
my $session_id;

$session_id = &make_session_id;

print "Session_ID: $session_id\n";  

 
sub make_session_id 
  {
  # $id = &make_session_id();
  # Erzeugt eine kryptographisch starke zufaellige Session ID.
  # Zurueckgegeben werden 24 Zeichen aus dem 64-Zeichen-Satz [A-Za-z0-9.-]
  # oder undef im Fehlerfall.
  # Plattformen ohne /dev/urandom koennen diese Routine nicht benutzen

  my $len = 24;
  my @session_chars = ('A' .. 'Z', 'a' .. 'z', 0 .. 9, '.', '-');
  my $id;
  eval 
    { open(RANDOM, "/dev/urandom") or die; };
  return (-1) if ($@);
  return (-2) unless (read(RANDOM, $id, $len) == $len);
  close(RANDOM);
  $id =~ s/(.)/$session_chars[ord($1) & 63]/esg;
  return $id;
  }
 
