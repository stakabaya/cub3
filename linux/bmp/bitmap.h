/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:45:36 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/18 09:48:18 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

# include <stdint.h>
# include "../constants.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
** "BM"をリトルエンディアンで解釈した値	B=0x42、M=0x4D
**< BMPファイルヘッダサイズ
**< Windowsヘッダサイズ
**< 標準のヘッダサイズ
*/
# define FILE_TYPE 0x4D42
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40
# define DEFAULT_HEADER_SIZE 54

/*
**< ファイルタイプ、必ず"BM"
**< ファイルサイズ
**< リザーブ
**< リザーブ
**< 先頭から画像情報までのオフセット、ヘッダ構造体＋パレットサイズ
*/
# pragma pack(2)

typedef struct		s_fileheader
{
	uint16_t		bf_type;
	uint32_t		bf_size;
	uint16_t		bf_reserved1;
	uint16_t		bf_reserved2;
	uint32_t		bf_off_bits;
}					t_fileheader;

# pragma pack()

/*
**< この構造体のサイズ
**< 画像の幅
**< 画像の高さ
**< 画像の枚数、通常1
**< 一色のビット数
**< 圧縮形式
**< 画像領域のサイズ
**< 画像の横方向解像度情報
**< 画像の縦方向解像度情報
**< カラーパレットのうち実際に使っている色の個数
**< カラーパレットのうち重要な色の数
*/
typedef struct		s_infoheader
{
	uint32_t		bi_size;
	int32_t			bi_width;
	int32_t			bi_height;
	uint16_t		bi_planes;
	uint16_t		bi_bit_count;
	uint32_t		bi_compression;
	uint32_t		bi_sizeimage;
	int32_t			bi_xpels_per_meter;
	int32_t			bi_ypels_per_meter;
	uint32_t		bi_cr_used;
	uint32_t		bi_clr_important;
}					t_infoheader;

#endif
