Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"FALL_LEFT"
    clock:70
Images:
    ?ImageList(str)<"00%s.png">{20,60-63}:
Groups:
    @start
        ?content(int)<%s>{0}:
    @main
        ?content(int)<%s>{1-4}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(start, 1)"
        "PLAY_GROUP(main, -1)"