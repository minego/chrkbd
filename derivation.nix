{ lib, stdenv, ...}:

stdenv.mkDerivation rec {
	name		= "chrkbd";
	version		= "0.0.1";
	src			= ./.;

	installPhase = ''
		mkdir -p $out/bin
		cp chrkbd $out/bin/
	'';

	meta = with lib; {
		homepage	= "https://github.com/minego/chrkbd";
		description	= "Improve the layout of the pixel slate detachable keyboard";
		license		= licenses.asl20; # Apache-2.0
		platforms	= platforms.linux;
	};
}

