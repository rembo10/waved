{ pkgs ? import <nixpkgs> {} }:
pkgs.stdenv.mkDerivation {
  name = "waved";
  src = ./.;

  nativeBuildInputs = [ pkgs.cmake ];

  buildPhase = "cmake --build .";

  installPhase = ''
    mkdir -p $out/bin
    cp waved $out/bin/
  '';
}
