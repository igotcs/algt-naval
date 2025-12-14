void salvarJogo(Jogador j1, Jogador j2, int turno) {
    FILE *f = fopen("save.dat", "wb");
    if(!f) return;

    fwrite(&j1, sizeof(Jogador), 1, f);
    fwrite(&j2, sizeof(Jogador), 1, f);
    fwrite(&turno, sizeof(int), 1, f);

    fclose(f);
