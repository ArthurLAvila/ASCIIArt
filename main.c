//
// Nome: Arthur Land Avila
// Versão: 1.1
// Data: 2020 10 20
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"

// Um pixel RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct {
    int width, height;
    RGB* img;
} Img;

// Protótipos
void load(char* name, Img* pic);

// Carrega uma imagem para a struct Img
void load(char* name, Img* pic)
{
    int chan;
    pic->img = (unsigned char*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

int main(int argc, char** argv)
{
    // Struct de Imagens
    Img pic, small_pic, char_pic;

    // Auxiliar para copia de RGB
    RGB aux1;

    // Variaveis de trabalho
    int tamanho_linear_imagem;
    int tamanho_linear_imagem_reduzida;
    int tamanho_linear_imagem_char;
    int x,y;
    int tom_de_cinza;
    int tom_de_cinza_medio;
    int tom_cinza_faixa;
    int num_pixels;

    // Gradiente de caracteres
    char mapa_caracters[9];
    strcpy(mapa_caracters, ".:coCO8@");

    // Carrega imagem passada no parâetro
    if(argc < 1) {
        printf("loader [img]\n");
        exit(1);
    }
    load(argv[1], &pic);

    // Imprime os 10 primeiros pixels da imagem para verificação
    printf("Primeiros 10 pixels da imagem:\n");
    for(int i=0; i<10; i++) {
        printf("[%02X %02X %02X] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
    }
    printf("\n");

    // Informa o tamanho da imagem para verificação
    printf("Tamanho original da imagem: %d x %d\n", pic.width, pic.height);
    
    // Calcula o tamanho linerar da imagem = tamanho do vetor imagem
    tamanho_linear_imagem = pic.width*pic.height;

    // Informa o tamanho linear da imegam
    printf("Tamanho linear da imagem: %d\n", tamanho_linear_imagem);

    // Copia imagem de pic para small_pic
    small_pic = pic;

    // Reduz o tamanho da imagem em 50% - não funciona
    //printf("Reduz imagem pela metade:\n");
    //y=0;
    //for (int l=0; l<pic.height; l+=2){
    //    x=0;
    //    for (int c=0; c<pic.width; c+=2) {
    //        small_pic.img[x+(y*small_pic.width/2)].r = pic.img[c+(l*pic.width)].r;
    //        x++;
    //    }
    //    y++;
    //}

    //printf("Calcula novo tamanho da imagem\n");
    //small_pic.width = pic.width/2;
    //small_pic.height = pic.height/2;

    //printf("Novo tamanho da imagem: %d x %d\n", small_pic.width, small_pic.height);

    tamanho_linear_imagem_reduzida = small_pic.width*small_pic.height;

    //printf("Tamanho linear da imagem reduzida: %d\n", tamanho_linear_imagem_reduzida);

    //printf("Primeiros 10 pixels da imagem reduzida:\n");
    //for(int i=0; i<10; i++) {
    //    printf("[%02X %02X %02X] ", small_pic.img[i].r, small_pic.img[i].g, small_pic.img[i].b);
    //}
    //printf("\n");
    
    //printf("Ultimos 10 pixels da imagem reduzida:\n");
    //for(int i=tamanho_linear_imagem_reduzida-10; i<tamanho_linear_imagem_reduzida; i++) {
    //    printf("[%02X %02X %02X] ", small_pic.img[i].r, small_pic.img[i].g, small_pic.img[i].b);
    //}
    //printf("\n");

    // Converte imagem para tons de cinza usando a formula sugerida
    printf("Converte imagem para tons de cinza:\n");
    for(int i=0; i<tamanho_linear_imagem_reduzida; i++) {
        aux1 = small_pic.img[i];
        tom_de_cinza = (0.3 * aux1.r + 0.59 * aux1.g + 0.11 * aux1.b);
        small_pic.img[i].r = tom_de_cinza;
        small_pic.img[i].g = tom_de_cinza;
        small_pic.img[i].b = tom_de_cinza;
    }

    // Imprime os 10 primeiros pixels da imagem em cinza para verificação
    printf("Primeiros 10 pixels da imagem em cinza:\n");
    for(int i=0; i<10; i++) {
        printf("[%02X %02X %02X] ", small_pic.img[i].r, small_pic.img[i].g, small_pic.img[i].b);
    }
    printf("\n");
    
    // Imprime os 10 ultimos pixels da imagem em cinza para verificação
    printf("Ultimos 10 pixels da imagem em cinza:\n");
    for(int i=tamanho_linear_imagem_reduzida-10; i<tamanho_linear_imagem_reduzida; i++) {
        printf("[%02X %02X %02X] ", small_pic.img[i].r, small_pic.img[i].g, small_pic.img[i].b);
    }
    printf("\n");


    // Copia imagem de small_pic para char_pic
    char_pic = small_pic;

    // Imprime alguns conjuntos de pixels 4x5 que serão convertidos para caracteres
    printf("Mostra alguns conjuntos de pixels 4x5:\n");
    for (int l=0; l<10; l++){
        for (int c=0; c<8; c++) {
            printf("[%02X %02X %02X] ", small_pic.img[c+(l*small_pic.width)].r, small_pic.img[c+(l*small_pic.width)].g, small_pic.img[c+(l*small_pic.width)].b);            
        }
        printf("\n");
    }

    // Converte imagem em cinza para caracteres 4x5
    printf("Converte imagem em cinza para caracteres 4x5:\n");
    for (int l=0; l<small_pic.height; l+=5){
        for (int c=0; c<small_pic.width; c+=4) {
            tom_de_cinza_medio = 0;
            num_pixels = 0;
            for(int l1=l; l1<l+5; l1++) {
                if (l1<small_pic.height) {
                  for (int c1=c; c1<c+4; c1++) {
                      if (c1<small_pic.width) {
                        // Soma todos os tons de cinza do quadrado 4x5
                        tom_de_cinza_medio += small_pic.img[c1+(l1*small_pic.width)].r;
                        num_pixels++;
                      }
                  }
                }
            }
            // Calcula o cinza médio do quadrado 4x5 (20 pixels)
            tom_de_cinza_medio = tom_de_cinza_medio/num_pixels;
            // Calcula o gradiente/faixa do cinza (256 tons de cinza / 8 caracteres_ou_faixas = 32)
            tom_cinza_faixa = tom_de_cinza_medio/32;
            // Coloca o gradiente/faixa na posição 1x1 do quadrado 4x5
            if (c+(l*small_pic.width) < tamanho_linear_imagem_reduzida) {
              char_pic.img[c+(l*small_pic.width)].r = tom_cinza_faixa;
            }
        }
    }


    // Calcula o tamanho da imagem 4x5
    printf("Calcula o tamanho da imagem 4x5\n");
    char_pic.width = small_pic.width/4;
    char_pic.height = small_pic.height/5;

    // Informa o novo tamanho da imagem 4x5
    printf("Novo tamanho da imagem caracter: %d x %d\n", char_pic.width, char_pic.height);

    // Calcula o tamanho linear da imagem 4x5
    tamanho_linear_imagem_char = char_pic.width * char_pic.height;
    printf("Tamanho linear da imagem caracter: %d\n", tamanho_linear_imagem_char);


    // Imprime os 10 primeiros pixels da imagem cinza em caracteres para verificação
    printf("Primeiros 10 pixels da imagem cinza em caracteres:\n");
    for(int i=0; i<10; i++) {
        printf("[%02X %02X %02X] ", char_pic.img[i].r, char_pic.img[i].g, char_pic.img[i].b);
    }
    printf("\n");
    
    // Imprime os 10 últimos pixels da imagem cinza em caracteres para verificação
    printf("Ultimos 10 pixels da imagem reduzida cinza em caracteres:\n");
    for(int i=tamanho_linear_imagem_char-10; i<tamanho_linear_imagem_char; i++) {
        printf("[%02X %02X %02X] ", char_pic.img[i].r, char_pic.img[i].g, char_pic.img[i].b);
    }
    printf("\n");


    // Imprime a imagem em caracters 4x5 - hora da verdade :-)
    printf("Imprime a imagem em caracteres:\n");
    printf("\n");

    printf("<html><head>ASCII Art</head>\n");
    printf("<body style='background: black;' leftmargin=0 topmargin=0>\n");
    printf("<style>\n");
    printf("pre  {\n");
    printf("         color: white;\n");
    printf("   font-family: Courier;\n");
    printf("   font-size: 8px;\n");
    printf("}\n");
    printf("</style>\n");
    printf("<pre>\n");

    for (int l=0; l<small_pic.height; l+=5){
        for (int c=0; c<small_pic.width; c+=4) {
            printf("%c", mapa_caracters[char_pic.img[c+(l*small_pic.width)].r]);
        }
        printf("\n");
    }

    printf("</pre>\n");
    printf("</body>\n");
    printf("</html>\n");

    // Escreve saida no arquivo html

    // Arquivo de saída
    FILE* arq = fopen("asciiart.html", "w");

    if (arq == NULL)
    {
        printf("Erro abrindo arquivo de saida");
        exit(1);
    }


    fprintf(arq, "<html><head>ASCII Art</head>\n");
    fprintf(arq, "<body style='background: black;' leftmargin=0 topmargin=0>\n");
    fprintf(arq, "<style>\n");
    fprintf(arq, "pre  {\n");
    fprintf(arq, "         color: white;\n");
    fprintf(arq, "   font-family: Courier;\n");
    fprintf(arq, "   font-size: 8px;\n");
    fprintf(arq, "}\n");
    fprintf(arq, "</style>\n");
    fprintf(arq, "<pre>\n");

    for (int l=0; l<small_pic.height; l+=5){
        for (int c=0; c<small_pic.width; c+=4) {
            fprintf(arq, "%c", mapa_caracters[char_pic.img[c+(l*small_pic.width)].r]);
        }
        fprintf(arq, "\n");
    }

    fprintf(arq, "</pre>\n");
    fprintf(arq, "</body>\n");
    fprintf(arq, "</html>\n");

    fclose(arq);

    // Libera memoria
    free(pic.img);
    free(small_pic.img);
    free(char_pic.img);
}
