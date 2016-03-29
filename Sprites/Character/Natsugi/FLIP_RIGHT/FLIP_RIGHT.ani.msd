Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"FLIP_RIGHT"
    play-mode:"ONETIME"
    clock:70
Images:
    ?ImageList(str)<"0%s.png">{105-112}:
Groups:
    @main
        ?content(int)<%s>{0-7}:
Animation:
    ?AnimationCode(str):
        "> PLAY_GROUP(main)"
        "> CALL('FALL_RIGHT')"