FROM consol/ubuntu-icewm-vnc
MAINTAINER Gleb Titov <liftchampion@gmail.com>
ENV REFRESHED_AT 2019-04-19

# Switch to root user to install additional software
USER 0

RUN apt-get update  -y && \
	apt-get install -y \
		gcc \
		git \
		make \
		libxext-dev \
		libx11-dev \
		zlib1g-dev

RUN \
	git clone https://github.com/liftchampion/minilibx.git && \
	mkdir -p /usr/X11 && \
	mkdir -p /usr/X11/include && \
	mkdir -p /usr/X11/lib && \
	mkdir -p /usr/local/lib && \
	cd minilibx && \
	cp include/mlx.h /usr/X11/include && \
	cp include/mlx.h /usr/local/include && \
	make && \
	cp libmlx.a /usr/X11/lib && \
	cp libmlx.a /usr/local/lib

## switch back to default user
USER 1000

RUN cd ~ && \
	git clone -b docker-demo https://github.com/liftchampion/lem_in.git && \
	cd lem_in && \
	mkdir -p cmp && \
	cp $(find -name '*.c' -o -name '*.h') ./cmp/ && \
	gcc -c ./cmp/*.c -w && \
	gcc -o lem_in *.o -lmlx -lXext -lX11 -lm -w && \
	rm -rf cmp && \
	rm -f *.o

RUN echo "echo '\\n'" >> /headless/.bashrc && \
	echo "./lem_in --help" >> /headless/.bashrc && \
	echo "echo '\\n'" >> /headless/.bashrc && \
	echo "./lem_in --usage" >> /headless/.bashrc && \
	echo "echo '\\n'" >> /headless/.bashrc && \
	echo "echo 'Test-files are in ./tests :'" >> /headless/.bashrc && \
	echo "ls tests" >> /headless/.bashrc
RUN cat /headless/.bashrc
WORKDIR /headless/lem_in
