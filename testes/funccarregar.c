int carregarJogo(Jogador *j1, Jogador *j2, int *turno) {
    FILE *f = fopen("save.dat", "rb");
    if(!f) return 0;

    fread(j1, sizeof(Jogador), 1, f);
    fread(j2, sizeof(Jogador), 1, f);
    fread(turno, sizeof(int), 1, f);

    fclose(f);
    return 1;
}
