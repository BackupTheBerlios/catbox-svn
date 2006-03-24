#!/usr/bin/perl
# Zustandserhaltung mit QUERY_STRING.

use strict;

use constant INITSTATE => 1;

my %FORM = ();
my $url = $ENV{'SERVER_NAME'} . $ENV{'SCRIPT_NAME'};
my $state      = retrieve_state();
my $nextstate  = compute_next_state($state);
my $saveaction = save_state($nextstate);

# Tue etwas abhaengig von $state:
print "Content-type: text/html\n\n";
print "<HTHL>", "\n";
print "<HEAD><TITLE>Status mit Query-String</TITLE></HEAD>\n";
print "<BODY>\n";
print "<B>Zustand: ", $state, "</B><P>";
print $saveaction;
print "</BODY></HTML>\n";


sub retrieve_state 
  {
  &parse_form;
  my $state = $FORM{'state'} || INITSTATE;
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
  my $send_back = "<A HREF=\"http://$url?state=$newstate\"> [Weiter] </A>";
  return $send_back;
  }

sub parse_form 
  {
  my ($buffer, @pairs, $pair, $name, $value);
  $buffer = $ENV{'QUERY_STRING'};
  @pairs = split(/&/, $buffer);
  foreach $pair (@pairs)
    {
    ($name, $value) = split(/=/, $pair);
    $value =~ tr/+/ /;
    $value =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;
    $FORM{$name} = $value;
    }
  }

