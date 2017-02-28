Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"CLIC"
    clock:10
    play-mode:"FORCE"
Images:
    ImageList:[1..9]
    model:"%s.png"
Groups:
    @main
        content:[8..0]
Animation:
    AnimationCode:[
        "PLAY_GROUP(main, 1)"
        "CALL('HOLD')"
    ]