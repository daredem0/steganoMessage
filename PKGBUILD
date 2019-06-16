pkgname="steganoMessage"
pkgver=0.3
pkgrel=1
pkgdesc="steganoMessage - commandline message hiding tool"
arch=("x86_64")
license=('MIT')
build(){
	cmake .
	make
}

package(){
	"make DESTDIR="$phgdir"	
}
