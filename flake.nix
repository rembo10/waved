{
  description = "Driver for the reMarkable 2 E-Ink display";

  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
    nixpkgs.url = "github:NixOS/nixpkgs";
  };

  outputs = inputs@{ self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in {
        defaultPackage = pkgs.stdenv.mkDerivation {
          name = "waved";
          src = ./.;
          nativeBuildInputs = [ pkgs.cmake ];
          buildPhase = "cmake --build .";
          installPhase = ''
            mkdir -p $out/bin
            cp waved $out/bin/
          '';
        };
      }
    );
}
