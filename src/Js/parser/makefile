
NAME = INScoreParser
OUT  = $(NAME).js

code : $(OUT)

$(OUT) : $(NAME).l.jison $(NAME).y.jison
	jison $(NAME).y.jison $(NAME).l.jison

clean:
	rm -f $(OUT)
