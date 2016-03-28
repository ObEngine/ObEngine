Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"SLIDE_LEFT"
    clock:70
Images:
    ?ImageList(str)<"0%s.png">{336-341}:
Groups:
    @start
        ?content(int)<%s>{0}:
    @main
        ?content(int)<%s>{1-5}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(start, 1)"
        "PLAY_GROUP(main, -1)"