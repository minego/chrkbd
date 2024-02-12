{ lib, stdenv, ...}:

stdenv.mkDerivation rec {
	name		= "swapmods";
	version		= "0.0.1";
	src			= ./.;

	installPhase = ''
		mkdir -p $out/bin
		cp swapmods $out/bin/
	'';

	meta = with lib; {
		homepage	= "https://github.com/minego/swapmods";
		description	= "Swap alt and super";
		license		= licenses.asl20; # Apache-2.0
		platforms	= platforms.linux;
	};
}

