Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"WALK_LEFT"
    clock:70
Images:
    ?ImageList(str)<"00%s.png">{35-42}:
Groups:
    @main
        ?content(int)<%s>{0-7}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(main, -1)"