#!/usr/bin/perl
#
# Automatisches Versenden einer E-Mail
# Programmaufruf:
# send.pl <Datei> <Empfaenger>
#
use strict;

# Folgende Variablen muessen vor Inbetriebnahme konfiguriert werden:
# ---------------------------------------------------------------------
# Pfad zum sendmail-Programm
my $MailProgram = '/usr/lib/sendmail -t';

# Absender der Automatik-Mail
#my $Mailfrom = 'automat@host.domain';
my $Mailfrom = 'plate@netzmafia.de';

# Betreff der E-Mail
my $Subject = 'Automatische E-Mail';

# Klartext-Nachricht
my $Message = "Dies ist eine automatisch generierte E-Mail\n";
$Message .= "mit einem Attachment.";

# ---------------------------------------------------------------------
############## AB HIER MUSS NICHTS MEHR GEAENDERT WERDEN ##############

my $Mailto = '';                 # Empfaenger der E-Mail
my $file = '';                   # zu sendende Datei
my $ext = '';                    # Datei-Extension
my $fext = '';                   # MIME-Typ dazu
my $buf = '';                    # Dateipuffer 
my $boundary = '';               # Mime-Begrenzer

die "Dateiangabe fehlt!" if ($ARGV[0] eq '');
die "Empfaengerangabe fehlt!" if ($ARGV[1] eq '');

$file = $ARGV[0];
$Mailto = $ARGV[1];

my @BoundaryChars = (0..9, 'A'..'F'); # Zeichen fuer Begrenzer

my %mime =                       # Mime-Typen
(
       #-------------------------------------<TEXT>-----
       'HTML',		"text/html",
       'HTM',		"text/html",
       'STM',		"text/html",
       'SHTML',		"text/html",
       'TXT',		"text/plain",
       'PREF',		"text/plain",
       'AIS',		"text/plain",
       'RTX',		"text/richtext",
       'TSV',		"text/tab-separated-values",
       'NFO',		"text/warez-info",
       'ETX',		"text/x-setext",
       'SGML',		"text/x-sgml",
       'SGM',		"text/x-sgml",
       'TALK',		"text/x-speech",
       'CGI',       "text/plain",
       'PL',        "text/plain",
       'C',         "text/plain",
       'CPP',       "text/plain",
       #-------------------------------------<IMAGE>----
       'BMP',       "image/bmp",
       'COD',       "image/cis-cod",
       'FID',       "image/fif",
       'GIF',       "image/gif",
       'ICO',       "image/ico",
       'IEF',       "image/ief",
       'JPEG',      "image/jpeg",
       'JPG',       "image/jpeg",
       'JPE',       "image/jpeg",
       'PNG',       "image/png",
       'TIF',       "image/tiff",
       'TIFF',      "image/tiff",
       'MCF',		"image/vasa",
       'RAS',		"image/x-cmu-raster",
       'CMX',		"image/x-cmx",
       'PCD',		"image/x-photo-cd",
       'PNM',		"image/x-portable-anymap",
       'PBM',		"image/x-portable-bitmap",
       'PGM',		"image/x-portable-graymap",
       'PPM',		"image/x-portable-pixmap",
       'RGB',		"image/x-rgb",
       'XBM',		"image/x-xbitmap",
       'XPM',		"image/x-xpixmap",
       'XWD',		"image/x-xwindowdump",
       #-------------------------------------<APPS>-----
       'EXE',		"application/octet-stream",
       'BIN',		"application/octet-stream",
       'DMS',		"application/octet-stream",
       'LHA',		"application/octet-stream",
       'CLASS',		"application/octet-stream",
       'DLL',		"application/octet-stream",
       'AAM',		"application/x-authorware-map",
       'AAS',		"application/x-authorware-seg",
       'AAB',		"application/x-authorware-bin",
       'VMD',		"application/vocaltec-media-desc",
       'VMF',		"application/vocaltec-media-file",
       'ASD',		"application/astound",
       'ASN',		"application/astound",
       'DWG',		"application/autocad",
       'DSP',		"application/dsptype",
       'DFX',		"application/dsptype",
       'EVY',		"application/envoy",
       'SPL',		"application/futuresplash",
       'IMD',		"application/immedia",
       'HQX',		"application/mac-binhex40",
       'CPT',		"application/mac-compactpro",
       'DOC',		"application/msword",
       'ODA',		"application/oda",
       'PDF',		"application/pdf",
       'AI',		"application/postscript",
       'EPS',		"application/postscript",
       'PS',		"application/postscript",
       'PPT',		"application/powerpoint",
       'RTF',		"application/rtf",
       'APM',		"application/studiom",
       'XAR',		"application/vnd.xara",
       'ANO',		"application/x-annotator",
       'ASP',		"application/x-asap",
       'CHAT',		"application/x-chat",
       'BCPIO',		"application/x-bcpio",
       'VCD',		"application/x-cdlink",
       'TGZ',		"application/x-compressed",
       'Z',		    "application/x-compress",
       'CPIO',		"application/x-cpio",
       'PUZ',		"application/x-crossword",
       'CSH',		"application/x-csh",
       'DCR',		"application/x-director",
       'DIR',		"application/x-director",
       'DXR',		"application/x-director",
       'FGD',		"application/x-director",
       'DVI',		"application/x-dvi",
       'LIC',		"application/x-enterlicense",
       'EPB',		"application/x-epublisher",
       'FAXMGR',	"application/x-fax-manager",
       'FAXMGRJOB',	"application/x-fax-manager-job",
       'FM',		"application/x-framemaker",
       'FRAME',		"application/x-framemaker",
       'FRM',		"application/x-framemaker",
       'MAKER',		"application/x-framemaker",
       'GTAR',		"application/x-gtar",
       'GZ',		"application/x-gzip",
       'HDF',		"application/x-hdf",
       'INS',		"application/x-insight",
       'INSIGHT',	"application/x-insight",
       'INST',		"application/x-install",
       'IV',		"application/x-inventor",
       'JS',		"application/x-javascript",
       'SKP',		"application/x-koan",
       'SKD',		"application/x-koan",
       'SKT',		"application/x-koan",
       'SKM',		"application/x-koan",
       'LATEX',		"application/x-latex",
       'LICMGR',	"application/x-licensemgr",
       'MAIL',		"application/x-mailfolder",
       'MIF',		"application/x-mailfolder",
       'NC',		"application/x-netcdf",
       'CDF',		"application/x-netcdf",
       'SDS',		"application/x-onlive",
       'SGI-LPR',	"application/x-sgi-lpr",
       'SH',		"application/x-sh",
       'SHAR',		"application/x-shar",
       'SWF',		"application/x-shockwave-flash",
       'SPRITE',	"application/x-sprite",
       'SPR',		"application/x-sprite",
       'SIT',		"application/x-stuffit",
       'SV4CPIO',	"application/x-sv4cpio",
       'SV4CRC',	"application/x-sv4crc",
       'TAR',		"application/x-tar",
       'TARDIST',	"application/x-tardist",
       'TCL',		"application/x-tcl",
       'TEX',		"application/x-tex",
       'TEXINFO',	"application/x-texinfo",
       'TEXI',		"application/x-texinfo",
       'T',		    "application/x-troff",
       'TR',		"application/x-troff",
       'TROFF',		"application/x-troff",
       'MAN',		"application/x-troff-man",
       'ME',		"application/x-troff-me",
       'MS',		"application/x-troff-ms",
       'TVM',		"application/x-tvml",
       'TVM',		"application/x-tvml",
       'USTAR',		"application/x-ustar",
       'SRC',		"application/x-wais-source",
       'WKZ',		"application/x-wingz",
       'ZIP',		"application/x-zip-compressed",
       'ZTARDIST',	"application/x-ztardist",
       #-------------------------------------<AUDIO>----
       'AU',		"audio/basic",
       'SND',		"audio/basic",
       'ES',		"audio/echospeech",
       'MID',		"audio/midi",
       'KAR',		"audio/midi",
       'MPGA',		"audio/mpeg",
       'MP2',		"audio/mpeg",
       'TSI',		"audio/tsplayer",
       'VOX',		"audio/voxware",
       'AIF',		"audio/x-aiff",
       'AIFC',		"audio/x-aiff",
       'AIFF',		"audio/x-aiff",
       'MID',		"audio/x-midi",
       'MP3',		"audio/x-mpeg",
       'MP2A',		"audio/x-mpeg2",
       'MPA2',		"audio/x-mpeg2",
       'M3U',		"audio/x-mpegurl",
       'MP3URL',	"audio/x-mpegurl",
       'PAT',		"audio/x-pat",
       'RAM',		"audio/x-pn-realaudio",
       'RPM',		"audio/x-pn-realaudio-plugin",
       'RA',		"audio/x-realaudio",
       'SBK',		"audio/x-sbk",
       'STR',		"audio/x-str",
       'WAV',		"audio/x-wav",
       #-------------------------------------<VIDEO>----
       'MPEG',		"video/mpeg",
       'MPG',		"video/mpeg",
       'MPE',		"video/mpeg",
       'QT',		"video/quicktime",
       'MOV',		"video/quicktime",
       'VIV',		"video/vivo",
       'VIVO',		"video/vivo",
       'MPS',		"video/x-mpeg-system",
       'SYS',		"video/x-mpeg-system",
       'MP2V',		"video/x-mpeg2",
       'MPV2',		"video/x-mpeg2",
       'AVI',		"video/x-msvideo",
       'MV',		"video/x-sgi-movie",
       'MOVIE',		"video/x-sgi-movie",
       #-------------------------------------<EXTRA>----
       'PDB',		"chemical/x-pdb",
       'XYZ',		"chemical/x-pdb",
       'CHM',		"chemical/x-cs-chemdraw",
       'SMI',		"chemical/x-daylight-smiles",
       'SKC',		"chemical/x-mdl-isis",
       'MOL',		"chemical/x-mdl-molfile",
       'RXN',		"chemical/x-mdl-rxn",
       'SMD',		"chemical/x-smd",
       'ACC',		"chemical/x-synopsys-accord",
       'ICE',		"x-conference/x-cooltalk",
       'SVR',		"x-world/x-svr",
       'WRL',		"x-world/x-vrml",
       'VRML',		"x-world/x-vrml",
       'VRJ',		"x-world/x-vrt",
       'VRJT',		"x-world/x-vrt",
);

	
# Begrenzer basteln
srand($$);
for (my $i = 0; $i++ < 24;)
  {
  $boundary .= $BoundaryChars[rand(@BoundaryChars)];
  }
$boundary = "Next_Part_" . $boundary;

#--------------------------------------------------- Send attatchments etc...
open MAIL, "| $MailProgram" || die "Cannot open $MailProgram";
print MAIL "To: $Mailto\n";
print MAIL "From: $Mailfrom\n";
print MAIL "X-Mailer: Fax-to-Mail-Gateway\n";
print MAIL "MIME-Version: 1.0\n";
print MAIL "Subject: $Subject\n";
print MAIL "Content-Type: multipart/mixed; boundary=\"$boundary\"\n";
print MAIL "\n";
print MAIL "This is a multi-part message in MIME format.\n";

print MAIL "--$boundary\n";
print MAIL "Content-Type: text/plain; charset=\"iso-8859-1\"\n";
print MAIL "Content-Transfer-Encoding: 8bit\n\n";
  	
print MAIL "\n\n$Message\n";

# Attachment anhaengen
($ext) = $file =~ m/\.([^\.]*)$/;
$ext =~ tr/a-z/A-Z/;
$fext = $mime{$ext};
if ($fext && $fext =~ /^text/) 
  {
  print MAIL "--$boundary\n";
  print MAIL "Content-Type: $fext; charset=\"iso-8859-1\"; name=\"$file\"\n";
  print MAIL "Content-Transfer-Encoding: 8bit\n";
  print MAIL "Content-Disposition: attachment; filename=\"$file\"\n\n";
  open INPUT, "$file";
  print MAIL while (<INPUT>);
  close INPUT;
  } 
else 
  {
  print MAIL "--$boundary\n";
  print MAIL "Content-Type: $fext; name=\"$file\"\n";
  print MAIL "Content-Transfer-Encoding: base64\n";
  print MAIL "Content-Disposition: attachment; filename=\"$file\"\n\n";
  
  $/=0;
  open INPUT, "$file" || die "Cannot open [$file].";
  binmode INPUT;
  while(read(INPUT, $buf, 60*57))
    {
    print MAIL &encode_base64($buf);
    }
  close INPUT;
  }    
# Attachment Ende

print MAIL "\n--$boundary--\n";
print MAIL "\n";
close MAIL;


sub encode_base64 
  {
  my $res = '';
  my $eol = "\n";
  my $padding;
  while (($_[0] =~ /(.{1,45})/gs))
    {
	$res .= substr(pack('u', $1), 1);
	chop $res;
    }
  $res =~ tr|` -_|AA-Za-z0-9+/|;       # translate from uuencode to base64
  $padding = (3 - length($_[0]) % 3) % 3;  # fix padding at the end
  $res =~ s/.{$padding}$/'=' x $padding/e if $padding; # Fix the end padding
  $res =~ s/(.{1,76})/$1$eol/g if (length $eol); # lines of at least 76 characters
  return $res;
  }

