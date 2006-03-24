#!/usr/local/bin/perl
#Holt E-Mails mit dem POP3-Protokoll

use Net::POP3;# aus libnet

# ----- CONFIGURATION ------------------------------------------
use constant MAILHOST => "mail.some.net"; # Der POP3-Server
use constant MAILUSER => "user";          # POP3-Account
use constant MAILPASS => "pass";          # oder User fragen
# ----- ab hier nichts mehr aendern ----------------------------

# Erzeuge ein POP3-Objekt
$pop3 = Net::POP3->new(MAILHOST,'Timeout' => 60)
    or die "can't create a new pop3 object: $!\n";

# Beim POP3-Server einloggen
$pop3->login(MAILUSER, MAILPASS)
    or die "can't login to the pop3 server: $!\n";

# Hole Liste aller noch nicht geloeschter Mails.
# Key: Nummer der nicht geloeschten Nachrichten,
# Value: Laenge der Nachricht in Bytes.
$phash = $pop3->list();

# Lies alle nicht geloeschten Mails
foreach my $elem (sort keys %{$phash}) 
  {
  # Hole die $elem-nte Mail
  my $ptext = $pop3->get($elem);

  # Nachricht ausgeben
  foreach my $line (@{$ptext}) 
    { print $line; }

  # OPTIONAL: Mail beim POP3-Server als geloescht markieren
  $pop3->delete($elem);
  }

$pop3->quit();
