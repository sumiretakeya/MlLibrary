/* Generated by Edge Impulse
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _EI_CLASSIFIER_MODEL_VARIABLES_H_
#define _EI_CLASSIFIER_MODEL_VARIABLES_H_

#include <stdint.h>
#include "model_metadata.h"
#include "anomaly_clusters.h"
#include "tflite-model/trained_model_compiled.h"
#include "edge-impulse-sdk/classifier/ei_model_types.h"
#include "edge-impulse-sdk/classifier/inferencing_engines/engines.h"

const char* ei_classifier_inferencing_categories[] = { "ArmCircles", "LateralRaises" };

uint8_t ei_dsp_config_3_axes[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
const uint32_t ei_dsp_config_3_axes_size = 9;
ei_dsp_config_spectral_analysis_t ei_dsp_config_3 = {
    3, // uint32_t blockId
    4, // int implementationVersion
    9, // int length of axes
    0.00125097350538f, // float scale-axes
    10, // int input-decimation-ratio
    "low", // select filter-type
    1.7578125f, // float filter-cutoff
    6, // int filter-order
    "FFT", // select analysis-type
    512, // int fft-length
    3, // int spectral-peaks-count
    0.1f, // float spectral-peaks-threshold
    "0.1, 0.5, 1.0, 2.0, 5.0", // string spectral-power-edges
    true, // boolean do-log
    false, // boolean do-fft-overlap
    1, // int wavelet-level
    "db10", // select wavelet
    false // boolean extra-low-freq
};

const size_t ei_dsp_blocks_size = 1;
ei_model_dsp_t ei_dsp_blocks[ei_dsp_blocks_size] = {
    { // DSP block 3
        855,
        &extract_spectral_analysis_features,
        (void*)&ei_dsp_config_3,
        ei_dsp_config_3_axes,
        ei_dsp_config_3_axes_size
    }
};

const ei_config_tflite_eon_graph_t ei_config_tflite_graph_0 = {
    .implementation_version = 1,
    .model_init = &trained_model_init,
    .model_invoke = &trained_model_invoke,
    .model_reset = &trained_model_reset,
    .model_input = &trained_model_input,
    .model_output = &trained_model_output,
};

const ei_learning_block_config_tflite_graph_t ei_learning_block_config_0 = {
    .implementation_version = 1,
    .block_id = 0,
    .object_detection = 0,
    .object_detection_last_layer = EI_CLASSIFIER_LAST_LAYER_UNKNOWN,
    .output_data_tensor = 0,
    .output_labels_tensor = 1,
    .output_score_tensor = 2,
    .graph_config = (void*)&ei_config_tflite_graph_0
};

const ei_learning_block_config_anomaly_kmeans_t ei_learning_block_config_1 = {
    .implementation_version = 1,
    .anom_axis = ei_classifier_anom_axes,
    .anom_axes_size = 9,
    .anom_clusters = ei_classifier_anom_clusters,
    .anom_cluster_count = 32,
    .anom_scale = ei_classifier_anom_scale,
    .anom_mean = ei_classifier_anom_mean,
};

const size_t ei_learning_blocks_size = 2;
const ei_learning_block_t ei_learning_blocks[ei_learning_blocks_size] = {
    {
        &run_nn_inference,
        (void*)&ei_learning_block_config_0,
    },
    {
        &run_kmeans_anomaly,
        (void*)&ei_learning_block_config_1,
    },
};

const ei_model_performance_calibration_t ei_calibration = {
    1, /* integer version number */
    false, /* has configured performance calibration */
    (int32_t)(EI_CLASSIFIER_RAW_SAMPLE_COUNT / ((EI_CLASSIFIER_FREQUENCY > 0) ? EI_CLASSIFIER_FREQUENCY : 1)) * 1000, /* Model window */
    0.8f, /* Default threshold */
    (int32_t)(EI_CLASSIFIER_RAW_SAMPLE_COUNT / ((EI_CLASSIFIER_FREQUENCY > 0) ? EI_CLASSIFIER_FREQUENCY : 1)) * 500, /* Half of model window */
    0   /* Don't use flags */
};


const ei_impulse_t impulse_239741_1 = {
    .project_id = 239741,
    .project_owner = "Sumire",
    .project_name = "stakeya-project-3",
    .deploy_version = 1,

    .nn_input_frame_size = 855,
    .raw_sample_count = 200,
    .raw_samples_per_frame = 9,
    .dsp_input_frame_size = 200 * 9,
    .input_width = 0,
    .input_height = 0,
    .input_frames = 0,
    .interval_ms = 10,
    .frequency = 100,
    .dsp_blocks_size = ei_dsp_blocks_size,
    .dsp_blocks = ei_dsp_blocks,
    
    .object_detection = 0,
    .object_detection_count = 0,
    .object_detection_threshold = 0,
    .object_detection_last_layer = EI_CLASSIFIER_LAST_LAYER_UNKNOWN,
    .fomo_output_size = 0,
    
    .tflite_output_features_count = 2,
    .learning_blocks_size = ei_learning_blocks_size,
    .learning_blocks = ei_learning_blocks,

    .inferencing_engine = EI_CLASSIFIER_TFLITE,
    
    .quantized = 1,
    
    .compiled = 1,

    .sensor = EI_CLASSIFIER_SENSOR_FUSION,
    .fusion_string = "accX + accY + accZ + gyrX + gyrY + gyrZ + magX + magY + magZ",
    .slice_size = (200/4),
    .slices_per_model_window = 4,

    .has_anomaly = 1,
    .label_count = 2,
    .calibration = ei_calibration,
    .categories = ei_classifier_inferencing_categories
};

const ei_impulse_t ei_default_impulse = impulse_239741_1;

#endif // _EI_CLASSIFIER_MODEL_METADATA_H_
