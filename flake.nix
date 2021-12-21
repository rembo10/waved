{
  description = "Driver for the reMarkable 2 E-Ink display";

  outputs = inputs@{ self, nixpkgs, ... }:
    let
      system = "armv7l-linux";
      pkgs = import nixpkgs { inherit system; };
    in {
      defaultPackage = pkgs.stdenv.mkDerivation {
        name = "waved";
        src = ./.;
        nativeBuildInputs = [ pkgs.buildPackages.cmake ];
        buildPhase = "cmake --build .";
        installPhase = ''
          mkdir -p $out/bin
          cp waved $out/bin/
        '';
      };
    };
}
