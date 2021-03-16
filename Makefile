.PHONY: all
all: libs


libs: glfw glew
	@echo "\033[32m libs builded \033[0m"

.PHONY: glfw
glfw:
	$(MAKE) -C cmake-build-debug/glfw
	cp cmake-build-debug/glfw/src/libglfw3.a .

.PHONY: glew
glew:
	$(MAKE) -C glew/auto
	$(MAKE) -C glew
	cp glew/lib/libGLEW.a .

.PHONY: clean
clean:
	rm -rf glew/auto/EGL-Registry glew/auto/OpenGL-Registry glew/auto/glfixes

.PHONY: fclean
fclean: clean
	rm -rf *.a