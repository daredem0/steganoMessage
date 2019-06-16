pkgname=stegmes
pkgver=0.4
pkgrel=1
pkgdesc="steganoMessage - commandline message hiding tool"
arch=("x86_64")
license=('MIT')
build(){
	cd ../
	pwd
	cmake .
	make
}

package(){
	cd ../
	make DESTDIR="$pkgdir/" install	
}