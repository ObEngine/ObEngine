Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"Paddle"
    clock:1000
Images:
    ?ImageList(string)<"paddle.png">{0}:
Groups:
    @main
        ?content(int)<%s>{0}:
Animation:
    ?AnimationCode(string):
        "PLAY_GROUP(main, -1)"