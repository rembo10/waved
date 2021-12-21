{ pkgs ? import <nixpkgs> {} }:
pkgs.stdenv.mkDerivation {
  name = "waved";
  src = ./.;

  nativeBuildInputs = [ pkgs.buildPackages.cmake ];

  buildPhase = "cmake --build .";

  installPhase = ''
    mkdir -p $out/bin
    cp waved $out/bin/
  '';
}
