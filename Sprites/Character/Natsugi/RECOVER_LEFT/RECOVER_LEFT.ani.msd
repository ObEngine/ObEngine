Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"RECOVER_LEFT"
    play-mode:"FORCE"
    clock:100
Images:
    ?ImageList(str)<"0%s.png">{853-858}:
Groups:
    @main
        ?content(int)<%s>{0-5}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(main, 1)"
        "CALL('FALL_LEFT')"