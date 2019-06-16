# Maintainer: Florian Leuze <FlorianLeuze@aol.com>
pkgname=stegmes
pkgver=0.4
pkgrel=3
pkgdesc="steganoMessage - commandline message hiding tool"
arch=("x86_64")
license=('MIT')
depends=('libjpeg-turbo'
	'libpng'
	'glew'
	'sfml'
	'glfw-x11')		
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
