namespace Emotiv
{
    using System;

    public class OptimizationParam
    {
        private IntPtr hOptimizationParam = EdkDll.EE_OptimizationParamCreate();

        ~OptimizationParam()
        {
            EdkDll.EE_OptimizationParamFree(this.hOptimizationParam);
        }

        public IntPtr GetHandle()
        {
            return this.hOptimizationParam;
        }

        public uint GetVitalAlgorithm(EdkDll.EE_EmotivSuite_t suite)
        {
            uint pVitalAlgorithmBitVectorOut = 0;
            EmoEngine.errorHandler(EdkDll.EE_OptimizationGetVitalAlgorithm(this.hOptimizationParam, suite, out pVitalAlgorithmBitVectorOut));
            return pVitalAlgorithmBitVectorOut;
        }

        public void SetVitalAlgorithm(EdkDll.EE_EmotivSuite_t suite, uint vitalAlgorithmBitVector)
        {
            EmoEngine.errorHandler(EdkDll.EE_OptimizationSetVitalAlgorithm(this.hOptimizationParam, suite, vitalAlgorithmBitVector));
        }
    }
}

