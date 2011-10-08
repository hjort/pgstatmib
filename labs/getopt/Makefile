all: testopt testoptlong

clean:
	rm -f testopt testoptlong

test: testopt
	./testopt
	./testopt -a -b
	./testopt -ab
	./testopt -c foo
	./testopt -cfoo
	./testopt arg1
	./testopt -a arg1
	./testopt -c foo arg1
	./testopt -a -- -b
	./testopt -a -

testlong:
	./testoptlong
	./testoptlong --verbose
	./testoptlong --brief
	./testoptlong --add
	./testoptlong -a
	./testoptlong --append
	./testoptlong -b
	./testoptlong --delete
	./testoptlong --delete what
	./testoptlong -d what
	./testoptlong --create what
	./testoptlong -cwhat
	./testoptlong --file what
	./testoptlong -f what
	./testoptlong anything
	./testoptlong --verbose --add -b --delete delete -c create --file file anything
