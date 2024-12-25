#ifndef DMA_PRIVATE_H
#define DMA_PRIVATE_H

#define NUMBERS_OF_STREAMS               8
#define NUMBERS_OF_CHANNELS              8
#define STREAM_EN_TIMEOUT                500 
#define DMA_CIRCULAR_MODE_MASK           0xFFFFFEFF
#define DMA_MODE_MASK                    0xFFFFFFFB
#define DMA_PL_MASK                      0xFFFCFFFF
#define DMA_FIFO_THRESHOLD_MASK          0xFFFFFFFC
#define DMA_CHANNEL_MASK                 0xF1FFFFFF
#define DMA_DIR_MASK                     0xFFFFFFCF
#define DMA_MEM_SIZE_MASK                0xFFFF9FFF
#define DMA_PERIPH_SIZE_MASK             0xFFFFE7FF
#define DMA_MEM_INC_MASK                 0xFFFFFBFF
#define DMA_PERIPH_INC_MASK              0xFFFFFDFF
#define DMA_IT_FLAGS                     5
#define DMA_IT_TYPES_MASK                0xFFFFFFE1





#endif