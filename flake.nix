{
  description = "Derivation for libff";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }: let
      pkgs = nixpkgs.legacyPackages.x86_64-linux;
      libff = pkgs.stdenv.mkDerivation {
        name = "libff";
        src = ./.;
        buildInputs = with pkgs; [ 
        gmp.dev
        procps
        openssl.dev
        libsodium
        libiop
        boost
        ];
        nativeBuildInputs = with pkgs; [
          pkg-config
          stdenv
          cmake
          git
        ];
      };
    in {
      packages.x86_64-linux.emscripten = emscripten;
      defaultPackage.x86_64-linux = self.packages.x86_64-linux.emscripten;
    };
}
