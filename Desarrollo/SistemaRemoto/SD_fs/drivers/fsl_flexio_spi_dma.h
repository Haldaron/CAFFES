/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _FSL_FLEXIO_SPI_DMA_H_
#define _FSL_FLEXIO_SPI_DMA_H_

#include "fsl_flexio_spi.h"
#include "fsl_dma.h"

/*!
 * @addtogroup flexio_dma_spi
 * @{
 */


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief  typedef for flexio_spi_master_dma_handle_t in advance. */
typedef struct _flexio_spi_master_dma_handle flexio_spi_master_dma_handle_t;

/*! @brief  Slave handle is the same with master handle. */
typedef flexio_spi_master_dma_handle_t flexio_spi_slave_dma_handle_t;

/*! @brief FlexIO SPI master callback for finished transmit */
typedef void (*flexio_spi_master_dma_transfer_callback_t)(FLEXIO_SPI_Type *base,
                                                          flexio_spi_master_dma_handle_t *handle,
                                                          status_t status,
                                                          void *userData);

/*! @brief FlexIO SPI slave callback for finished transmit */
typedef void (*flexio_spi_slave_dma_transfer_callback_t)(FLEXIO_SPI_Type *base,
                                                         flexio_spi_slave_dma_handle_t *handle,
                                                         status_t status,
                                                         void *userData);

/*! @brief FlexIO SPI DMA transfer handle, users should not touch the content of the handle.*/
struct _flexio_spi_master_dma_handle
{
    size_t transferSize;                                /*!< Total bytes to be transferred. */
    bool txInProgress;                                  /*!< Send transfer in progress */
    bool rxInProgress;                                  /*!< Receive transfer in progress */
    dma_handle_t *txHandle;                             /*!< DMA handler for SPI send */
    dma_handle_t *rxHandle;                             /*!< DMA handler for SPI receive */
    flexio_spi_master_dma_transfer_callback_t callback; /*!< Callback for SPI DMA transfer */
    void *userData;                                     /*!< User Data for SPI DMA callback */
};

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name DMA Transactional
 * @{
 */

/*!
 * @brief Initializes the FLEXO SPI master DMA handle.
 *
 * This function initializes the FLEXO SPI master DMA handle which can be used for other FLEXO SPI master transactional
 * APIs.
 * Usually, for a specified FLEXO SPI instance, call this API once to get the initialized handle.
 *
 * @param base Pointer to FLEXIO_SPI_Type structure.
 * @param handle Pointer to flexio_spi_master_dma_handle_t structure to store the transfer state.
 * @param callback SPI callback, NULL means no callback.
 * @param userData callback function parameter.
 * @param txHandle User requested DMA handle for FlexIO SPI RX DMA transfer.
 * @param rxHandle User requested DMA handle for FlexIO SPI TX DMA transfer.
 * @retval kStatus_Success Successfully create the handle.
 * @retval kStatus_OutOfRange The FlexIO SPI DMA type/handle table out of range.
 */
status_t FLEXIO_SPI_MasterTransferCreateHandleDMA(FLEXIO_SPI_Type *base,
                                                  flexio_spi_master_dma_handle_t *handle,
                                                  flexio_spi_master_dma_transfer_callback_t callback,
                                                  void *userData,
                                                  dma_handle_t *txHandle,
                                                  dma_handle_t *rxHandle);

/*!
 * @brief Performs a non-blocking FlexIO SPI transfer using DMA.
 *
 * @note This interface returned immediately after transfer initiates. Call
 * FLEXIO_SPI_MasterGetTransferCountDMA to poll the transfer status to check
 * whether the FlexIO SPI transfer is finished.
 *
 * @param base Pointer to FLEXIO_SPI_Type structure.
 * @param handle Pointer to flexio_spi_master_dma_handle_t structure to store the transfer state.
 * @param xfer Pointer to FlexIO SPI transfer structure.
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_FLEXIO_SPI_Busy FlexIO SPI is not idle, is running another transfer.
 */
status_t FLEXIO_SPI_MasterTransferDMA(FLEXIO_SPI_Type *base,
                                      flexio_spi_master_dma_handle_t *handle,
                                      flexio_spi_transfer_t *xfer);

/*!
 * @brief Aborts a FlexIO SPI transfer using DMA.
 *
 * @param base Pointer to FLEXIO_SPI_Type structure.
 * @param handle FlexIO SPI DMA handle pointer.
 */
void FLEXIO_SPI_MasterTransferAbortDMA(FLEXIO_SPI_Type *base, flexio_spi_master_dma_handle_t *handle);

/*!
 * @brief Gets the remaining bytes for FlexIO SPI DMA transfer.
 *
 * @param base Pointer to FLEXIO_SPI_Type structure.
 * @param handle FlexIO SPI DMA handle pointer.
 * @param count Number of bytes transferred so far by the non-blocking transaction.
 */
status_t FLEXIO_SPI_MasterTransferGetCountDMA(FLEXIO_SPI_Type *base,
                                              flexio_spi_master_dma_handle_t *handle,
                                              size_t *count);

/*!
 * @brief Initializes the FlexIO SPI slave DMA handle.
 *
 * This function initializes the FlexIO SPI slave DMA handle.
 *
 * @param base Pointer to FLEXIO_SPI_Type structure.
 * @param handle Pointer to flexio_spi_slave_dma_handle_t structure to store the transfer state.
 * @param callback SPI callback, NULL means no callback.
 * @param userData callback function parameter.
 * @param txHandle User requested DMA handle for FlexIO SPI TX DMA transfer.
 * @param rxHandle User requested DMA handle for FlexIO SPI RX DMA transfer.
 */
static inline void FLEXIO_SPI_SlaveTransferCreateHandleDMA(FLEXIO_SPI_Type *base,
                                                           flexio_spi_slave_dma_handle_t *handle,
                                                           flexio_spi_slave_dma_transfer_callback_t callback,
                                                           void *userData,
                                                           dma_handle_t *txHandle,
                                                           dma_handle_t *rxHandle)
{
    FLEXIO_SPI_MasterTransferCreateHandleDMA(base, handle, callback, userData, txHandle, rxHandle);
}

/*!
 * @brief Performs a non-blocking FlexIO SPI transfer using DMA.
 *
 * @note This interface returns immediately after transfer initiates. Call
 * FLEXIO_SPI_SlaveGetTransferCountDMA to poll the transfer status and
 * check whether the FlexIO SPI transfer is finished.
 *
 * @param base Pointer to FLEXIO_SPI_Type structure.
 * @param handle Pointer to flexio_spi_slave_dma_handle_t structure to store the transfer state.
 * @param xfer Pointer to FlexIO SPI transfer structure.
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_FLEXIO_SPI_Busy FlexIO SPI is not idle, is running another transfer.
 */
status_t FLEXIO_SPI_SlaveTransferDMA(FLEXIO_SPI_Type *base,
                                     flexio_spi_slave_dma_handle_t *handle,
                                     flexio_spi_transfer_t *xfer);

/*!
 * @brief Aborts a FlexIO SPI transfer using DMA.
 *
 * @param base Pointer to FLEXIO_SPI_Type structure.
 * @param handle Pointer to flexio_spi_slave_dma_handle_t structure to store the transfer state.
 */
static inline void FLEXIO_SPI_SlaveTransferAbortDMA(FLEXIO_SPI_Type *base, flexio_spi_slave_dma_handle_t *handle)
{
    FLEXIO_SPI_MasterTransferAbortDMA(base, handle);
}

/*!
 * @brief Gets the remaining bytes to be transferred for FlexIO SPI DMA.
 *
 * @param base Pointer to FLEXIO_SPI_Type structure.
 * @param handle FlexIO SPI DMA handle pointer.
 * @param count Number of bytes transferred so far by the non-blocking transaction.
 */
static inline status_t FLEXIO_SPI_SlaveTransferGetCountDMA(FLEXIO_SPI_Type *base,
                                                           flexio_spi_slave_dma_handle_t *handle,
                                                           size_t *count)
{
    return FLEXIO_SPI_MasterTransferGetCountDMA(base, handle, count);
}

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif
