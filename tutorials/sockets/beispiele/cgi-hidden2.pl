#!/usr/bin/perl
#Zustandserhaltung mit Hidden-Feldern.

use strict;
use CGI qw(:standard);

use constant INITSTATE => 1;

my $state      = retrieve_state();
my $nextstate  = compute_next_state($state);
my $saveaction = save_state($nextstate);

# Tue etwas abhaengig von $state:
print header;
print start_html('Status mit Hidden Fields');
print '<B>Zustand: ', $state,'</B><P>';
print '<FORM METHOD="POST">';
print $saveaction;
print '<INPUT TYPE="submit" NAME="submit" VALUE=" Abschicken ">';
print '</FORM>';
print end_html;


sub retrieve_state 
  {
  my $state = param('state') || INITSTATE;
  return $state;
  }

sub compute_next_state 
  {
  my $current_state = shift;
  return $current_state + 1;
  }

sub save_state 
  {
  my $newstate = shift;
  my $send_back = "<INPUT TYPE=\"hidden\" NAME=\"state\" VALUE=\"$newstate\">";
  return $send_back;
  }
