#!/usr/bin/perl
#Zustandserhaltung mit Hidden-Feldern.

use strict;

use constant INITSTATE => 1;

my %FORM = ();
my $url = 'http://' . $ENV{'SERVER_NAME'} . $ENV{'SCRIPT_NAME'};
my $state      = retrieve_state();
my $nextstate  = compute_next_state($state);
my $saveaction = save_state($nextstate);

# Tue etwas abhaengig von $state:
print "Content-type: text/html\n\n";
print "<HTHL>", "\n";
print "<HEAD><TITLE>Status mit hidden fields</TITLE></HEAD>\n";
print "<BODY>\n";
print "<B>Zustand: $state </B><P>";
print "<FORM METHOD=\"POST\" ACTION=\"$url\">\n";
print $saveaction;
print '<INPUT TYPE="submit" NAME="submit" VALUE=" Abschicken ">';
print "</FORM>\n";
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
  my $send_back = "<INPUT TYPE=\"hidden\" NAME=\"state\" VALUE=\"$newstate\">";
  return $send_back;
  }

sub parse_form 
  {
  my ($buffer, @pairs, $pair, $name, $value);
  if ($ENV{'REQUEST_METHOD'} eq 'GET') 
    { @pairs = split(/&/, $ENV{'QUERY_STRING'}); }
  elsif ($ENV{'REQUEST_METHOD'} eq 'POST') 
    {
    @pairs = split(/&/, $buffer);
    read(STDIN, $buffer, $ENV{'CONTENT_LENGTH'});
    }
  @pairs = split(/&/, $buffer);
  foreach $pair (@pairs)
    {
    ($name, $value) = split(/=/, $pair);
    $value =~ tr/+/ /;
    $value =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;
    $FORM{$name} = $value;
    }
  }

