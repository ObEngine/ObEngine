Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"FALLKICK_RIGHT"
    play-mode:"FORCE"
    clock:0
Images:
    ?ImageList(str)<"0%s.png">{304-311}:
Groups:
    @start
        clock:50
        ?content(int)<%s>{0-3}:
    @main
        clock:70
        ?content(int)<%s>{4-7}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(start, 1)"
        "PLAY_GROUP(main, 1)"