using Dreamteck.Splines;
using UnityEngine;

public sealed class SpawnCheckpoints
{
    #region Parameters
    private readonly GameObject checkpoint = null;
    private readonly SplineComputer splineComputer = null;
    private readonly Color[] colors;
    private readonly float checkpointsSpawnDelta = 0.0f;
    #endregion

    public SpawnCheckpoints(SplineComputer splineComputer, GameObject checkpoint, Color[] checkpointColors, float checkpointsSpawnDelta)
    {
        this.splineComputer = splineComputer;
        this.checkpoint = checkpoint;
        colors = checkpointColors;
        this.checkpointsSpawnDelta = checkpointsSpawnDelta;
    }

    #region Custom methods
    public void CrateCheckpoints()
    {
        float splineLength = splineComputer.CalculateLength();
        float fullLengthInPercent = 100, currentDistance = 0;
        int checkpointColorIndex = 0;

        while (currentDistance <= splineLength)
        {
            currentDistance += checkpointsSpawnDelta;

            if (currentDistance >= splineLength) return;

            GameObject checkpoint = CreateCheckpoint(currentDistance, fullLengthInPercent, splineLength);
            checkpoint.transform.SetParent(splineComputer.transform);

            Color color = colors[checkpointColorIndex];
            checkpointColorIndex = ++checkpointColorIndex % colors.Length;

            PaintCheckpoint(checkpoint, color);
        }
    }

    private GameObject CreateCheckpoint(float currentDistance, float fullLengthInPercent, float splineLength)
    {
        double percent = ((currentDistance * fullLengthInPercent) / splineLength) / fullLengthInPercent;
        double savePercent = Mathf.Clamp01((float)percent);

        SplineSample splineSample = splineComputer.Evaluate(savePercent);

        return Object.Instantiate(checkpoint, splineSample.position, splineSample.rotation);
    }

    private void PaintCheckpoint(GameObject checkpoint, Color color)
    {
        if (checkpoint.TryGetComponent(out CheckpointBehaviour checkpointBehaviour))
        {
            checkpointBehaviour.ChangeCheckpointColor(color);
        }

        if (checkpoint.TryGetComponent(out ParticleSystem particleSystem))
        {
            ParticleSystem.MainModule main = particleSystem.main;
            main.startColor = new ParticleSystem.MinMaxGradient(color);
        }
    }
    #endregion
}
