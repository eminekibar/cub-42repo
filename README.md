# 🎮 cub3D - 42 İstanbul Projesi

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue.svg" alt="C">
  <img src="https://img.shields.io/badge/42-İstanbul-success.svg" alt="42 İstanbul">
  <img src="https://img.shields.io/badge/OS-Linux-orange.svg" alt="Linux">
</p>

## 📖 İçindekiler

1. [Proje Hakkında](#-proje-hakkında)
2. [Proje Yapısı](#-proje-yapısı)
3. [Kurulum ve Derleme](#-kurulum-ve-derleme)
4. [Kullanım](#-kullanım)
5. [Raycasting Algoritması](#-raycasting-algoritması)
   - [Temel Kavramlar](#temel-kavramlar)
   - [Matematiksel Formüller](#matematiksel-formüller)
   - [DDA Algoritması](#dda-algoritması)
   - [Duvar Projeksiyon Hesaplaması](#duvar-projeksiyon-hesaplaması)
6. [Harita Parse Sistemi](#-harita-parse-sistemi)
   - [Dosya Formatı](#dosya-formatı)
   - [Texture Parsing](#texture-parsing)
   - [Renk Parsing](#renk-parsing)
   - [Harita Doğrulama](#harita-doğrulama)
   - [Flood Fill Algoritması](#flood-fill-algoritması)
7. [Oyuncu Hareket Sistemi](#-oyuncu-hareket-sistemi)
   - [Hareket Formülleri](#hareket-formülleri)
   - [Dönüş Matrisi](#dönüş-matrisi)
   - [Çarpışma Algılama](#çarpışma-algılama)
8. [Texture Mapping](#-texture-mapping)
9. [Veri Yapıları](#-veri-yapıları)
10. [Kod Akışı](#-kod-akışı)
11. [Hata Yönetimi](#-hata-yönetimi)
12. [Geliştiren Ekip](#-geliştiren-ekip)

---

## 🎯 Proje Hakkında

**cub3D**, 1990'lardaki ilk FPS oyunlarından ilham alan (özellikle Wolfenstein 3D) bir **ray-casting** oyun motorudur. Bu proje, **MiniLibX** grafik kütüphanesini kullanarak pseudo-3D bir görünüm oluşturur.

### Proje Özellikleri
- ✅ 2D haritadan 3D perspektif oluşturma
- ✅ Dört yön texture desteği (Kuzey, Güney, Doğu, Batı)
- ✅ Özelleştirilebilir tavan ve zemin renkleri
- ✅ WASD ve ok tuşları ile hareket
- ✅ Kapsamlı harita doğrulama sistemi
- ✅ Memory leak'siz güvenli çıkış

### Kullanılan Teknolojiler
- **Dil:** C (C99)
- **Grafik:** MiniLibX
- **Kütüphane:** libft (42 standart kütüphane)
- **Matematiksel fonksiyonlar:** math.h (cos, sin, fabs, floor)

---

## 📁 Proje Yapısı

```
cub-42repo/
├── includes/
│   └── cub3d.h              # Ana header dosyası
├── srcs/
│   ├── main.c               # Program giriş noktası
│   ├── engine/              # Render motoru
│   │   ├── raycast_init.c   # Ray başlatma
│   │   ├── raycast_dda.c    # DDA algoritması
│   │   ├── raycast_project.c# Projeksiyon hesaplama
│   │   ├── raycast_draw.c   # Dünya çizimi
│   │   ├── render.c         # Render döngüsü
│   │   ├── textures.c       # Texture işlemleri
│   │   └── window.c         # Pencere yönetimi
│   ├── hooks/               # Kullanıcı girişi
│   │   ├── hooks.c          # Event handler'lar
│   │   ├── hooks_helpers.c  # Yardımcı fonksiyonlar
│   │   ├── move_player.c    # Oyuncu hareketi
│   │   ├── rotate_player.c  # Oyuncu dönüşü
│   │   └── setup_player_vectors.c # Başlangıç vektörleri
│   ├── parser/              # Harita parser
│   │   ├── parser.c         # Ana parser
│   │   ├── parser_utils.c   # Yardımcı fonksiyonlar
│   │   ├── parse_color.c    # Renk parsing
│   │   ├── parse_color_utils.c # Renk yardımcıları
│   │   ├── parse_textures.c # Texture parsing
│   │   ├── handle_map_line.c# Harita satırı işleme
│   │   ├── finalize_map.c   # Harita sonlandırma
│   │   ├── flood_fill.c     # Flood fill algoritması
│   │   ├── duplicate_grid.c # Grid kopyalama
│   │   └── gnl/             # get_next_line
│   └── utils/               # Yardımcı modüller
│       ├── init_game.c      # Oyun başlatma
│       ├── error.c          # Hata yönetimi
│       └── memory.c         # Bellek yönetimi
├── lib/
│   ├── libft/               # 42 standart kütüphane
│   └── minilibx-linux/      # MiniLibX kütüphanesi
├── maps/
│   ├── valid/               # Geçerli haritalar
│   └── invalid/             # Test için geçersiz haritalar
├── textures/
│   └── basic/               # XPM texture dosyaları
└── Makefile
```

---

## 🔧 Kurulum ve Derleme

### Gereksinimler
- Linux işletim sistemi
- GCC derleyici
- Make
- X11 kütüphaneleri (libXext, libX11)

### Derleme Komutları

```bash
# Projeyi derle
make

# Temizle
make clean

# Tam temizle
make fclean

# Yeniden derle
make re
```

### Makefile Yapısı

```makefile
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -O0
LFLAGS = -L$(LIBFT_PATH) -lft -L$(MLX_PATH) -lmlx
MLXFLAGS = -lXext -lX11 -lm -lz
```

---

## 🕹️ Kullanım

```bash
./cub3D <harita_dosyası.cub>
```

### Örnek
```bash
./cub3D maps/valid/subject_map.cub
```

### Kontroller

| Tuş | İşlev |
|-----|-------|
| `W` | İleri git |
| `S` | Geri git |
| `A` | Sola kayma (strafe) |
| `D` | Sağa kayma (strafe) |
| `←` | Sola dön |
| `→` | Sağa dön |
| `ESC` | Çıkış |

---

## 🔬 Raycasting Algoritması

### Temel Kavramlar

Raycasting, 2D haritadan pseudo-3D görüntü oluşturan bir render tekniğidir. Her ekran sütunu için bir ışın gönderilir ve bu ışının bir duvara çarpana kadar ilerletilmesiyle duvarın konumu belirlenir.

#### Koordinat Sistemi

```
     Y-
      ↑
      |
X- ←--+-→ X+
      |
      ↓
     Y+
```

- **Oyuncu konumu (pos):** Harita üzerindeki gerçek koordinatlar
- **Yön vektörü (dir):** Oyuncunun baktığı yön (birim vektör)
- **Kamera düzlemi (plane):** FOV'u belirleyen vektör

### Matematiksel Formüller

#### 1. Kamera X Koordinatı Hesaplaması

Her ekran sütunu için kamera uzayındaki x koordinatı hesaplanır:

```c
camera_x = 2.0 * x / (double)WIN_W - 1.0;
```

**Açıklama:**
- `x`: Ekran sütunu (0 ile WIN_W-1 arası)
- Sonuç: -1 (sol kenar) ile +1 (sağ kenar) arası

| Ekran sütunu | camera_x değeri |
|--------------|-----------------|
| 0 | -1.0 |
| WIN_W/2 | 0.0 |
| WIN_W-1 | ~1.0 |

#### 2. Işın Yönü (Ray Direction) Hesaplaması

```c
ray_dir_x = player.dir.x + player.plane.x * camera_x;
ray_dir_y = player.dir.y + player.plane.y * camera_x;
```

**Formül:**
```
ray_dir = dir + plane * camera_x
```

Bu formül, oyuncunun bakış yönünden kamera düzleminin genişliğine göre ışını yayar.

**Görsel açıklama:**
```
          plane.x * camera_x
              ←─────→
                 ╱
                ╱ ray_dir
               ╱
              ╱
  Oyuncu ────────────→ dir
             ╲
              ╲
               ╲ ray_dir
                ╲
```

#### 3. Delta Distance Hesaplaması

Bir hücreden diğerine geçerken kat edilen mesafe:

```c
if (ray_dir_x == 0.0)
    delta_dist_x = __DBL_MAX__;
else
    delta_dist_x = fabs(1.0 / ray_dir_x);

if (ray_dir_y == 0.0)
    delta_dist_y = __DBL_MAX__;
else
    delta_dist_y = fabs(1.0 / ray_dir_y);
```

**Formül:**
```
Δdist_x = |1 / ray_dir_x|
Δdist_y = |1 / ray_dir_y|
```

**Matematiksel temeli:**

Işın yönü `(ray_dir_x, ray_dir_y)` birim vektör olmak zorunda değildir. Delta distance, ışının x veya y ekseninde bir birim ilerlemesi için kat edeceği toplam mesafeyi verir.

```
Işının bir grid hücresini geçmesi:

     |         |
     |    ╱    |
     |   ╱     |
  ───┼──╱──────┼───
     | ╱       |
     |╱        |
  ───┼─────────┼───
     |         |
```

#### 4. İlk Adım Mesafesi (Side Distance)

Işının ilk grid sınırına kadar olan mesafesi:

```c
// X ekseni için
if (ray_dir_x < 0.0)
{
    step_x = -1;
    side_dist_x = (player.pos.x - map_x) * delta_dist_x;
}
else
{
    step_x = 1;
    side_dist_x = (map_x + 1.0 - player.pos.x) * delta_dist_x;
}

// Y ekseni için (benzer mantık)
if (ray_dir_y < 0.0)
{
    step_y = -1;
    side_dist_y = (player.pos.y - map_y) * delta_dist_y;
}
else
{
    step_y = 1;
    side_dist_y = (map_y + 1.0 - player.pos.y) * delta_dist_y;
}
```

**Örnek hesaplama:**
```
Oyuncu pozisyonu: (2.3, 1.7)
map_x = 2, map_y = 1
ray_dir_x = 0.6, ray_dir_y = 0.8 (sağ-aşağı doğru)

delta_dist_x = |1/0.6| = 1.667
delta_dist_y = |1/0.8| = 1.25

step_x = 1 (sağa)
step_y = 1 (aşağı)

side_dist_x = (2 + 1.0 - 2.3) * 1.667 = 0.7 * 1.667 = 1.167
side_dist_y = (1 + 1.0 - 1.7) * 1.25  = 0.3 * 1.25  = 0.375
```

### DDA Algoritması

**Digital Differential Analyzer (DDA)**, ışının hangi harita hücrelerinden geçtiğini verimli bir şekilde hesaplayan algoritmadır.

#### Algoritma Mantığı

```c
void ray_run_dda(t_game *game)
{
    game->hit.hit = 0;
    while (!game->hit.hit)
    {
        // Hangi eksen daha yakın?
        if (game->ray.side_dist_x < game->ray.side_dist_y)
        {
            game->ray.side_dist_x += game->ray.delta_dist_x;
            game->ray.map_x += game->ray.step_x;
            game->hit.side = 0; // X ekseni (Doğu/Batı duvarı)
        }
        else
        {
            game->ray.side_dist_y += game->ray.delta_dist_y;
            game->ray.map_y += game->ray.step_y;
            game->hit.side = 1; // Y ekseni (Kuzey/Güney duvarı)
        }
        
        // Sınır kontrolü
        if (!in_bounds(game, game->ray.map_x, game->ray.map_y))
            break;
            
        // Duvar kontrolü
        if (game->map.grid[game->ray.map_y][game->ray.map_x] == '1')
            game->hit.hit = 1;
    }
}
```

#### DDA Görsel Açıklama

```
Örnek ışın ilerleyişi:

     0   1   2   3   4   5   6
   ┌───┬───┬───┬───┬───┬───┬───┐
 0 │ 1 │ 1 │ 1 │ 1 │ 1 │ 1 │ 1 │
   ├───┼───┼───┼───┼───┼───┼───┤
 1 │ 1 │   │   │ ░ │░░░│ 1 │ 1 │  ← Işın yolu ░
   ├───┼───┼───┼───┼───┼───┼───┤     
 2 │ 1 │   │ ░ │   │   │   │ 1 │
   ├───┼───┼───┼───┼───┼───┼───┤
 3 │ 1 │ P │   │   │   │   │ 1 │  P = Oyuncu
   ├───┼───┼───┼───┼───┼───┼───┤
 4 │ 1 │ 1 │ 1 │ 1 │ 1 │ 1 │ 1 │
   └───┴───┴───┴───┴───┴───┴───┘

DDA Adımları:
1. (1,3) → side_dist karşılaştır
2. x daha yakın → (2,3) git
3. y daha yakın → (2,2) git
4. x daha yakın → (3,2) git
5. y daha yakın → (3,1) git
6. x daha yakın → (4,1) git
7. hit = 1 (duvar '1' ile karşılaşıldı)
```

### Duvar Projeksiyon Hesaplaması

#### Perpendicular Wall Distance (Dik Duvar Mesafesi)

**Neden dik mesafe kullanılır?**

Gerçek Öklid mesafesi kullanılsaydı, ekranın kenarlarındaki duvarlar ortadakilere göre daha uzak görünürdü ("fish-eye" efekti). Dik mesafe bu sorunu ortadan kaldırır.

```c
void ray_project(t_game *game)
{
    if (!game->hit.hit)
        game->hit.perp_wall_dist = __DBL_MAX__;
    else if (game->hit.side == 0)  // X-side (Doğu/Batı)
        game->hit.perp_wall_dist = (game->ray.map_x - game->player.pos.x
                + (1 - game->ray.step_x) / 2.0) / game->ray.ray_dir_x;
    else  // Y-side (Kuzey/Güney)
        game->hit.perp_wall_dist = (game->ray.map_y - game->player.pos.y
                + (1 - game->ray.step_y) / 2.0) / game->ray.ray_dir_y;
}
```

**Formül açıklaması:**

X-side için:
```
perp_wall_dist = (map_x - pos.x + (1 - step_x) / 2) / ray_dir_x
```

Burada `(1 - step_x) / 2` terimi:
- `step_x = 1` ise → 0 (hücrenin sol kenarı)
- `step_x = -1` ise → 1 (hücrenin sağ kenarı)

#### Duvar Yüksekliği Hesaplaması

```c
game->hit.line_h = (int)((double)WIN_H / game->hit.perp_wall_dist);
```

**Formül:**
```
line_height = WIN_H / perp_wall_dist
```

Mesafe arttıkça duvar yüksekliği azalır, bu da perspektif etkisi oluşturur.

#### Çizim Sınırları

```c
game->hit.draw_start = -game->hit.line_h / 2 + WIN_H / 2;
if (game->hit.draw_start < 0)
    game->hit.draw_start = 0;
    
game->hit.draw_end = game->hit.line_h / 2 + WIN_H / 2;
if (game->hit.draw_end >= WIN_H)
    game->hit.draw_end = WIN_H - 1;
```

**Açıklama:**
- Duvar, ekranın ortasına göre ortalanır
- Ekran sınırlarını aşan kısımlar kırpılır (clipping)

```
Ekran düzeni:
     ┌────────────────┐
     │    TAVAN       │  ← 0 to draw_start
     ├────────────────┤
     │                │
     │    DUVAR       │  ← draw_start to draw_end
     │                │
     ├────────────────┤
     │    ZEMİN       │  ← draw_end to WIN_H
     └────────────────┘
```

---

## 📋 Harita Parse Sistemi

### Dosya Formatı

`.cub` uzantılı harita dosyası aşağıdaki bölümlerden oluşur:

```
NO textures/basic/path_to_the_north_texture.xpm
SO textures/basic/path_to_the_south_texture.xpm
WE textures/basic/path_to_the_west_texture.xpm
EA textures/basic/path_to_the_east_texture.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Dosya Bölümleri

| Tanımlayıcı | Açıklama | Format |
|-------------|----------|--------|
| `NO` | Kuzey texture | `NO ./path/to/texture.xpm` |
| `SO` | Güney texture | `SO ./path/to/texture.xpm` |
| `WE` | Batı texture | `WE ./path/to/texture.xpm` |
| `EA` | Doğu texture | `EA ./path/to/texture.xpm` |
| `F` | Zemin rengi | `F R,G,B` |
| `C` | Tavan rengi | `C R,G,B` |

### Harita Karakterleri

| Karakter | Anlamı |
|----------|--------|
| `0` | Boş alan (yürünebilir) |
| `1` | Duvar |
| `N` | Oyuncu (kuzey yönü) |
| `S` | Oyuncu (güney yönü) |
| `E` | Oyuncu (doğu yönü) |
| `W` | Oyuncu (batı yönü) |
| ` ` (boşluk) | Harita dışı alan |

### Texture Parsing

```c
void parse_texture(t_game *game, char **target_path, char **tokens)
{
    // Format kontrolü: sadece 2 token olmalı (ID + path)
    if (tokens[1] == NULL || tokens[2] != NULL)
        exit_safe(game, "Invalid texture format (Ex. 'NO ./path')", 1);
    
    // Tekrar tanımlama kontrolü
    if (*target_path != NULL)
        exit_safe(game, "Texture path duplicate detected", 1);
    
    // Path temizleme ve doğrulama
    clean_texture_token(game, &tokens[1]);
    validate_texture_file(game, tokens[1]);
    
    *target_path = ft_strdup(tokens[1]);
}
```

#### Texture Doğrulamaları

1. **Uzantı kontrolü:** `.xpm` ile bitmeli
2. **Dosya erişimi:** Dosya okunabilir olmalı
3. **Gizli dosya kontrolü:** `.` ile başlamamalı

### Renk Parsing

```c
void parse_color(t_game *game, int *target_color, char **tokens)
{
    check_color_tokens(game, target_color, tokens);
    
    // RGB değerlerini ayır
    game->parser_state.rgb_colors = split_and_check_rgb(game, tokens[1]);
    
    // Her değeri integer'a çevir
    r = lunatoi(game, game->parser_state.rgb_colors[0]);
    g = lunatoi(game, game->parser_state.rgb_colors[1]);
    b = lunatoi(game, game->parser_state.rgb_colors[2]);
    
    // Aralık kontrolü
    check_rgb_range(game, r, g, b);  // 0-255 arası
    
    // Tek integer'a birleştir
    final_color = (r << 16) | (g << 8) | b;
    *target_color = final_color;
}
```

#### Renk Formülü

```
RGB → Integer dönüşümü:

color = (R << 16) | (G << 8) | B

Örnek: RGB(220, 100, 0)
  R = 220 → 220 << 16 = 0xDC0000
  G = 100 → 100 << 8  = 0x006400  
  B = 0   → 0         = 0x000000
  ────────────────────────────────
  color = 0xDC0000 | 0x006400 | 0x000000 = 0xDC6400

Bit düzeni:
  ┌──────────┬──────────┬──────────┐
  │   RED    │  GREEN   │   BLUE   │
  │ 23....16 │ 15.....8 │ 7......0 │
  └──────────┴──────────┴──────────┘
```

### Harita Doğrulama

Harita aşağıdaki koşulları sağlamalıdır:

1. **Karakter kontrolü:** Sadece `01NSEW` ve boşluk
2. **Oyuncu kontrolü:** Tam olarak 1 oyuncu olmalı
3. **Kapalı harita:** Harita duvarlarla çevrili olmalı

```c
void validate_map_content(t_game *game)
{
    int player_count;
    char **map_copy;
    
    // Karakterleri ve oyuncu sayısını kontrol et
    check_map_chars_and_player(game, &player_count);
    
    if (player_count != 1)
        exit_safe(game, "There should be 1 player on the map.", 1);
    
    // Flood fill ile kapalılık kontrolü
    map_copy = duplicate_grid(game, &game->map);
    flood_fill(game, map_copy, 
        (int)game->player.pos.x, (int)game->player.pos.y);
    free_grid(map_copy);
}
```

### Flood Fill Algoritması

Haritanın duvarlarla tamamen çevrili olduğunu doğrulamak için kullanılır:

```c
void flood_fill(t_game *game, char **map_copy, int x, int y)
{
    // Dikey sınır kontrolü
    if (y < 0 || y >= game->map.height || map_copy[y] == NULL)
    {
        free_grid(map_copy);
        exit_safe(game, "Map open vertically", 1);
    }
    
    // Yatay sınır kontrolü
    if (x < 0 || x >= (int)ft_strlen(map_copy[y]))
    {
        free_grid(map_copy);
        exit_safe(game, "Map open horizontally", 1);
    }
    
    // Duvar veya ziyaret edilmiş
    if (map_copy[y][x] == '1' || map_copy[y][x] == 'F')
        return;
    
    // Boşluk karakteri = harita açık
    if (map_copy[y][x] == ' ')
    {
        free_grid(map_copy);
        exit_safe(game, "There should be no gaps in the map!", 1);
    }
    
    // Ziyaret edildi olarak işaretle
    if (ft_strchr("0NSEW", map_copy[y][x]))
        map_copy[y][x] = 'F';
    
    // Dört yöne rekursif devam
    flood_fill(game, map_copy, x, y + 1);
    flood_fill(game, map_copy, x, y - 1);
    flood_fill(game, map_copy, x + 1, y);
    flood_fill(game, map_copy, x - 1, y);
}
```

#### Flood Fill Görselleştirmesi

```
Başlangıç:           Flood Fill sonrası:
┌─────────────┐      ┌─────────────┐
│ 1 1 1 1 1 1 │      │ 1 1 1 1 1 1 │
│ 1 0 0 0 0 1 │      │ 1 F F F F 1 │
│ 1 0 N 0 0 1 │  →   │ 1 F F F F 1 │
│ 1 0 0 0 0 1 │      │ 1 F F F F 1 │
│ 1 1 1 1 1 1 │      │ 1 1 1 1 1 1 │
└─────────────┘      └─────────────┘
                     Tüm 0 ve N → F oldu
                     = Harita kapalı ✓
```

```
Açık harita örneği:
┌─────────────┐
│ 1 1 1 1 1 1 │
│ 1 0 0   0 1 │  ← Boşluk var!
│ 1 0 N 0 0 1 │
│ 1 0 0 0 0 1 │
│ 1 1 1 1 1 1 │
└─────────────┘
= HATA: "There should be no gaps in the map!"
```

---

## 🎮 Oyuncu Hareket Sistemi

### Başlangıç Vektörleri

Oyuncunun başlangıç yönüne göre vektörleri ayarlanır:

```c
void setup_player_vectors(t_game *game)
{
    if (game->player.current_direction == 'N')
        set_player_north(game);
    else if (game->player.current_direction == 'S')
        set_player_south(game);
    else if (game->player.current_direction == 'W')
        set_player_west(game);
    else if (game->player.current_direction == 'E')
        set_player_east(game);
}
```

| Yön | dir (x, y) | plane (x, y) |
|-----|-----------|--------------|
| Kuzey (N) | (0, -1) | (0.66, 0) |
| Güney (S) | (0, 1) | (-0.66, 0) |
| Batı (W) | (-1, 0) | (0, -0.66) |
| Doğu (E) | (1, 0) | (0, 0.66) |

**FOV (Field of View) = 0.66** 

Bu değer yaklaşık 66 derecelik görüş alanı sağlar. `plane` vektörünün uzunluğu FOV'u belirler.

### Hareket Formülleri

#### İleri Hareket (W)

```c
void go_forward(t_game *game)
{
    move_player(game, 
        game->player.dir.x * MOVE_SPEED, 
        game->player.dir.y * MOVE_SPEED);
}
```

**Formül:**
```
new_pos = old_pos + dir * MOVE_SPEED
```

#### Geri Hareket (S)

```c
void go_down(t_game *game)
{
    move_player(game, 
        -game->player.dir.x * MOVE_SPEED, 
        -game->player.dir.y * MOVE_SPEED);
}
```

**Formül:**
```
new_pos = old_pos - dir * MOVE_SPEED
```

#### Strafe Hareketi (A/D)

**Sol strafe:**
```c
void go_left(t_game *game)
{
    move_player(game, 
        game->player.dir.y * MOVE_SPEED, 
        -game->player.dir.x * MOVE_SPEED);
}
```

**Sağ strafe:**
```c
void go_right(t_game *game)
{
    move_player(game, 
        -game->player.dir.y * MOVE_SPEED, 
        game->player.dir.x * MOVE_SPEED);
}
```

**Strafe vektörü hesaplaması:**
```
dir = (dx, dy)
left_strafe  = (dy, -dx)   → dir'e 90° sola dik
right_strafe = (-dy, dx)   → dir'e 90° sağa dik
```

### Dönüş Matrisi

#### 2D Rotasyon Matrisi

```c
static void rotate_vector(t_vec2 *vector, double cos, double sin)
{
    double x;
    
    x = vector->x;
    vector->x = (vector->x * cos) - (vector->y * sin);
    vector->y = (x * sin) + (vector->y * cos);
}

static void rotate_player(t_game *game, double rotate_angle)
{
    double rot_cos;
    double rot_sin;
    
    rot_cos = cos(rotate_angle);
    rot_sin = sin(rotate_angle);
    rotate_vector(&game->player.dir, rot_cos, rot_sin);
    rotate_vector(&game->player.plane, rot_cos, rot_sin);
}
```

**Matematiksel formül:**

2D rotasyon matrisi:
```
┌ x' ┐   ┌ cos(θ)  -sin(θ) ┐   ┌ x ┐
│    │ = │                 │ × │   │
└ y' ┘   └ sin(θ)   cos(θ) ┘   └ y ┘
```

Açık formül:
```
x' = x * cos(θ) - y * sin(θ)
y' = x * sin(θ) + y * cos(θ)
```

- **Sola dönüş:** θ = -ROTATE_SPEED (negatif açı)
- **Sağa dönüş:** θ = +ROTATE_SPEED (pozitif açı)

### Çarpışma Algılama

```c
static void move_player(t_game *game, double dx, double dy)
{
    double new_x;
    double new_y;
    int map_x;
    int map_y;
    
    new_x = game->player.pos.x + dx;
    new_y = game->player.pos.y + dy;
    
    // X ekseni kontrolü
    if (dx > 0)
        map_x = (int)(new_x + PLAYER_MARGIN);
    else
        map_x = (int)(new_x - PLAYER_MARGIN);
    map_y = (int)(game->player.pos.y);
    
    if (is_walkable(&game->map, map_y, map_x))
        game->player.pos.x = new_x;
    
    // Y ekseni kontrolü (benzer mantık)
    map_x = (int)(game->player.pos.x);
    if (dy > 0)
        map_y = (int)(new_y + PLAYER_MARGIN);
    else
        map_y = (int)(new_y - PLAYER_MARGIN);
    
    if (is_walkable(&game->map, map_y, map_x))
        game->player.pos.y = new_y;
}
```

**PLAYER_MARGIN = 0.125**

Bu değer, oyuncunun duvarlara çok yaklaşmasını engeller:

```
┌─────────────────────┐
│         1           │
│                     │
│     ┌───────┐       │
│     │ margin│       │
│     │  ●    │       │  ● = Oyuncu merkezi
│     │       │       │  □ = Margin bölgesi
│     └───────┘       │
│                     │
│         1           │
└─────────────────────┘
```

---

## 🖼️ Texture Mapping

### XPM Yükleme

```c
void load_textures(t_game *game, char *path, int i)
{
    game->texture[i].img = mlx_xpm_file_to_image(
            game->mlx.mlx_ptr, path,
            &game->texture[i].width,
            &game->texture[i].height);
    
    if (!game->texture[i].img)
        exit_safe(game, "Texture yüklenemedi!", 1);
    
    game->texture[i].addr = mlx_get_data_addr(
            game->texture[i].img,
            &game->texture[i].bpp,
            &game->texture[i].line_len,
            &game->texture[i].endian);
}
```

### Duvar Hit Pozisyonu

Texture'ün X koordinatı (U koordinatı):

```c
if (game->hit.side == 0)  // X-side
    wall_hit_pos = game->player.pos.y 
        + game->hit.perp_wall_dist * game->ray.ray_dir_y;
else  // Y-side
    wall_hit_pos = game->player.pos.x 
        + game->hit.perp_wall_dist * game->ray.ray_dir_x;

texture_u = wall_hit_pos - floor(wall_hit_pos);  // Ondalık kısım (0-1 arası)
game->hit.tex_x = (int)(texture_u * (double)game->texture[tex_idx].width);
```

### Texture Y Koordinatı

```c
d = y * 256 - WIN_H * 128 + game->hit.line_h * 128;
game->hit.tex_y = ((d * game->texture[tex_idx].height) / game->hit.line_h) / 256;
```

Bu formül, duvar şeridinin her pikselini texture'daki karşılık gelen pikselle eşler.

### Texture Mirror Düzeltmesi

```c
if ((game->hit.side == 0 && game->ray.step_x < 0)
    || (game->hit.side == 1 && game->ray.step_y > 0))
    game->hit.tex_x = game->texture[tex_idx].width - game->hit.tex_x - 1;
```

Bu, texture'ların duvarın hangi tarafından bakıldığına göre doğru yönde görünmesini sağlar.

### Texture Seçimi

```c
void ray_pick_color(t_game *game, int y)
{
    if (game->hit.side == 0)  // X-side (Doğu/Batı)
    {
        if (game->ray.step_x > 0)
            game->hit.color = sample_texture(game, TEX_EAST, y);
        else
            game->hit.color = sample_texture(game, TEX_WEST, y);
    }
    else  // Y-side (Kuzey/Güney)
    {
        if (game->ray.step_y > 0)
            game->hit.color = sample_texture(game, TEX_SOUTH, y);
        else
            game->hit.color = sample_texture(game, TEX_NORTH, y);
    }
}
```

| Durum | Seçilen Texture |
|-------|-----------------|
| side=0, step_x>0 | Doğu (EA) |
| side=0, step_x<0 | Batı (WE) |
| side=1, step_y>0 | Güney (SO) |
| side=1, step_y<0 | Kuzey (NO) |

---

## 📊 Veri Yapıları

### Ana Oyun Yapısı

```c
typedef struct s_game
{
    t_mlx           mlx;           // MiniLibX bağlamı
    t_player        player;        // Oyuncu durumu
    t_map           map;           // Harita verileri
    t_parser_state  parser_state;  // Parser durumu
    t_input         input;         // Klavye durumu
    t_ray           ray;           // Işın hesaplama
    t_hit           hit;           // Çarpışma bilgisi
    t_texture       *texture;      // 4 duvar texture'ı
}   t_game;
```

### Işın Yapısı

```c
typedef struct s_ray
{
    double  camera_x;      // Kamera uzayı x (-1 ile +1 arası)
    double  ray_dir_x;     // Işın yönü x bileşeni
    double  ray_dir_y;     // Işın yönü y bileşeni
    int     map_x;         // Harita hücresi x
    int     map_y;         // Harita hücresi y
    double  side_dist_x;   // Sonraki x sınırına mesafe
    double  side_dist_y;   // Sonraki y sınırına mesafe
    double  delta_dist_x;  // Bir x hücresi atlama mesafesi
    double  delta_dist_y;  // Bir y hücresi atlama mesafesi
    int     step_x;        // X yönü adım (-1 veya +1)
    int     step_y;        // Y yönü adım (-1 veya +1)
}   t_ray;
```

### Çarpışma Bilgisi

```c
typedef struct s_hit
{
    int     hit;            // Duvar vuruldu mu?
    int     side;           // 0=x-side, 1=y-side
    double  perp_wall_dist; // Dik duvar mesafesi
    int     line_h;         // Duvar çizgi yüksekliği
    int     draw_start;     // Çizim başlangıç y
    int     draw_end;       // Çizim bitiş y
    int     color;          // Piksel rengi
    int     tex_x;          // Texture x koordinatı
    int     tex_y;          // Texture y koordinatı
}   t_hit;
```

### Oyuncu Yapısı

```c
typedef struct s_player
{
    t_vec2  pos;               // Pozisyon (x, y)
    t_vec2  dir;               // Bakış yönü
    t_vec2  plane;             // Kamera düzlemi
    char    current_direction; // Başlangıç yönü (N/S/E/W)
}   t_player;
```

### Harita Yapısı

```c
typedef struct s_map
{
    char    **grid;                // 2D harita dizisi
    char    **map_copy;            // Flood fill için kopya
    int     width;                 // Harita genişliği
    int     height;                // Harita yüksekliği
    char    *north_texture_path;   // NO texture yolu
    char    *south_texture_path;   // SO texture yolu
    char    *west_texture_path;    // WE texture yolu
    char    *east_texture_path;    // EA texture yolu
    int     floor_color;           // Zemin rengi
    int     ceiling_color;         // Tavan rengi
    t_list  *line_list;            // Parse sırasında satır listesi
    int     is_map_started;        // Harita bölümü başladı mı?
}   t_map;
```

---

## 🔄 Kod Akışı

### Program Akışı Diyagramı

```
main()
  │
  ├─→ ft_memset(&game, 0, sizeof(t_game))
  │   └── Tüm değerleri sıfırla
  │
  ├─→ validate_arguments()
  │   ├── argc == 2 kontrolü
  │   ├── .cub uzantı kontrolü
  │   └── Gizli dosya kontrolü
  │
  ├─→ init_game()
  │   ├── MiniLibX başlat
  │   └── 4 texture için bellek ayır
  │
  ├─→ parse_map_lines()
  │   ├── Dosyayı aç
  │   └── Her satır için:
  │       ├── process_identifier()
  │       │   ├── NO/SO/WE/EA → parse_texture()
  │       │   ├── F/C → parse_color()
  │       │   └── diğer → handle_map_line()
  │       └── Bellek temizle
  │
  ├─→ finalize_map_grid()
  │   ├── line_list → grid dönüşümü
  │   └── line_list temizle
  │
  ├─→ validate_map_content()
  │   ├── Karakter kontrolü
  │   ├── Tek oyuncu kontrolü
  │   └── flood_fill() ile kapalılık kontrolü
  │
  ├─→ setup_player_vectors()
  │   └── Başlangıç yönüne göre dir ve plane ayarla
  │
  ├─→ create_window()
  │   ├── Pencere oluştur
  │   ├── Image buffer oluştur
  │   ├── Texture'ları yükle
  │   ├── Hook'ları kaydet
  │   └── mlx_loop() → render döngüsü başlat
  │
  └─→ exit_safe()
      └── Temiz çıkış
```

### Render Döngüsü

```
mlx_loop_hook → game_loop()
  │
  ├─→ apply_input()
  │   ├── W tuşu → go_forward()
  │   ├── S tuşu → go_down()
  │   ├── A tuşu → go_left()
  │   ├── D tuşu → go_right()
  │   ├── ← tuşu → turn_left()
  │   └── → tuşu → turn_right()
  │
  ├─→ draw_background()
  │   ├── Üst yarı: ceiling_color
  │   └── Alt yarı: floor_color
  │
  ├─→ draw_world()
  │   └── Her sütun için (x = 0 to WIN_W):
  │       ├── ray_init(x)
  │       ├── ray_step_init()
  │       ├── ray_run_dda()
  │       ├── ray_project()
  │       └── Her piksel için (y = draw_start to draw_end):
  │           ├── ray_pick_color(y)
  │           └── put_pixel(x, y, color)
  │
  └─→ mlx_put_image_to_window()
      └── Buffer'ı ekrana çiz
```

---

## ⚠️ Hata Yönetimi

### Hata Türleri ve Mesajları

| Kategori | Hata Mesajı | Açıklama |
|----------|------------|----------|
| **Argüman** | `Usage: ./cub3D <map_file.cub>` | Yanlış argüman sayısı |
| **Argüman** | `The map file name must have the .cub extension.` | Yanlış uzantı |
| **Argüman** | `The map file cannot be hidden` | Gizli dosya |
| **Dosya** | `File cannot open` | Dosya açılamadı |
| **Texture** | `Invalid texture format (Ex. 'NO ./path')` | Yanlış format |
| **Texture** | `Texture path duplicate detected` | Tekrar tanımlama |
| **Texture** | `Texture path must end with .xpm` | Yanlış uzantı |
| **Texture** | `This file cannot be read` | Texture okunamadı |
| **Texture** | `Texture yüklenemedi!` | XPM yükleme hatası |
| **Renk** | `Invalid color tokens` | Yanlış renk formatı |
| **Renk** | `RGB value has invalid sign` | Geçersiz işaret |
| **Renk** | `RGB value is too large` | Çok büyük değer |
| **Harita** | `The map is empty` | Boş harita |
| **Harita** | `Invalid char found in the map` | Geçersiz karakter |
| **Harita** | `There should be 1 player on the map.` | Oyuncu sayısı ≠ 1 |
| **Harita** | `Map open vertically` | Dikey açık harita |
| **Harita** | `Map open horizontally` | Yatay açık harita |
| **Harita** | `There should be no gaps in the map!` | Haritada boşluk |
| **Bellek** | `Malloc (map grid)` | Bellek ayırma hatası |

### Güvenli Çıkış

```c
void exit_safe(t_game *game, char *str, int exit_no)
{
    if (ft_strlen(str) > 0)
        ft_putendl_fd(str, 2);
    
    // Tüm kaynakları temizle
    free_textures_and_images_and_grid(game);
    free_map_paths(game);
    free_mlx_and_window(game);
    
    exit(exit_no);
}
```

---

## 🧪 Test Haritaları

### Geçerli Haritalar (`maps/valid/`)

| Dosya | Açıklama |
|-------|----------|
| `subject_map.cub` | Proje konu haritası |
| `test_map.cub` | Basit test haritası |
| `square_map.cub` | Kare harita |
| `cheese_maze.cub` | Labirent haritası |
| `matrix.cub` | Karmaşık harita |
| `creepy.cub` | Korku temalı |
| `dungeon.cub` | Zindan temalı |
| `library.cub` | Kütüphane temalı |

### Geçersiz Haritalar (`maps/invalid/`)

| Dosya | Test Edilen Hata |
|-------|------------------|
| `empty.cub` | Boş dosya |
| `player_none.cub` | Oyuncu yok |
| `player_multiple.cub` | Birden fazla oyuncu |
| `player_on_edge.cub` | Kenarda oyuncu |
| `wall_hole_*.cub` | Açık duvar |
| `textures_missing.cub` | Eksik texture |
| `textures_duplicates.cub` | Tekrarlı texture |
| `color_invalid_rgb.cub` | Geçersiz RGB |
| `map_first.cub` | Harita önce gelmiş |

---

## 📐 Sabitler

| Sabit | Değer | Açıklama |
|-------|-------|----------|
| `WIN_W` | 1024 | Pencere genişliği (piksel) |
| `WIN_H` | 768 | Pencere yüksekliği (piksel) |
| `FOV` | 0.66 | Görüş alanı (~66°) |
| `MOVE_SPEED` | 0.07 | Hareket hızı |
| `ROTATE_SPEED` | 0.05 | Dönüş hızı (radyan) |
| `PLAYER_MARGIN` | 0.125 | Çarpışma margin'i |
| `TEX_NORTH` | 0 | Kuzey texture indeksi |
| `TEX_SOUTH` | 1 | Güney texture indeksi |
| `TEX_WEST` | 2 | Batı texture indeksi |
| `TEX_EAST` | 3 | Doğu texture indeksi |

---

## 👥 Geliştiren Ekip

| 👤 Geliştirici | 📧 İletişim |
|---------------|------------|
| **ekibar** | ekibar@student.42istanbul.com.tr |
| **azorlutu** | azorlutu@student.42istanbul.com.tr |

---

## 📚 Kaynaklar

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - Raycasting referans kaynağı
- [42 cub3D Subject](https://projects.intra.42.fr/projects/cub3d) - Proje konusu
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Grafik kütüphanesi

---

<p align="center">
  <i>42 İstanbul - 2025</i>
</p>
