use strict;

sub start_log #(Dateiname)
  {
  my $filename = shift;
  open(FH,">>".$filename) || return 0;
  chmod($filename,644);
  my $oldfh = select(FH);   # Autoflush
  $| = 1; # Autoflush für FH
  select($oldfh);
  flock(FH,8);
  $SIG{__WARN__} = \&log_warn;
  $SIG{__DIE__} = \&log_die;
  return 1;
  }

sub end_log
  {
  close(FH);
  }

sub log_info #(Message)
  {
  my $time = localtime;
  my $mesg = join(' ',@_) || "Oops!";
  $mesg = $time . " [INFO] " . $mesg . "\n";
  flock(FH,2);
  print FH $mesg;
  flock(FH,8);
  }

sub log_warn #(Message)
  {
  my $time = localtime;
  my $mesg = join(' ',@_) || "Oops!";
  $mesg = $time . " [ERROR] " . $mesg . "\n";
  flock(FH,2);
  print FH $mesg;
  flock(FH,8);
  }

sub log_die #(Message)
  {
  my $time = localtime;
  my $mesg = join(' ',@_) || "Oops!";
  $mesg = $time . " [FATAL] " . $mesg . "\n";
  flock(FH,2);
  print FH $mesg;
  flock(FH,8);
  close(FH);
  die @_;
  }

