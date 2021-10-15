using Dreamteck.Splines;
using UnityEngine;

public sealed class SpawnCheckpoints
{
    private readonly GameObject checkpoint = null;
    private readonly SplineComputer splineComputer = null;
    private readonly Color[] colors;
    private readonly float checkpointsSpawnDelta = 0.0f;

    public SpawnCheckpoints(SplineComputer splineComputer, GameObject checkpoint, Color[] checkpointColors, float checkpointsSpawnDelta)
    {
        this.splineComputer = splineComputer;
        this.checkpoint = checkpoint;
        colors = checkpointColors;
        this.checkpointsSpawnDelta = checkpointsSpawnDelta;
    }

    public void CrateCheckpoints()
    {
        float splineLength = splineComputer.CalculateLength();
        float fullLengthInPercent = 100, currentDistance = 0;
        int checkpointColorIndex = 0;

        while (currentDistance <= splineLength)
        {
            currentDistance += checkpointsSpawnDelta;

            if (currentDistance >= splineLength) return;

            double percent = ((currentDistance * fullLengthInPercent) / splineLength) / fullLengthInPercent;
            double savePercent = Mathf.Clamp01((float)percent);

            SplineSample splineSample = splineComputer.Evaluate(savePercent);

            GameObject checkpointGO = Object.Instantiate(checkpoint, splineSample.position, splineSample.rotation);

            if (checkpointGO.TryGetComponent(out CheckpointBehaviour checkpointBehaviour))
            {
                checkpointColorIndex = ++checkpointColorIndex % colors.Length;
                Color color = colors[checkpointColorIndex];

                checkpointBehaviour.ChangeCheckpointColor(color);

                if(checkpointGO.TryGetComponent(out ParticleSystem particleSystem))
                {
                    ParticleSystem.MainModule main = particleSystem.main;
                    main.startColor = new ParticleSystem.MinMaxGradient(color);
                }
            }

            checkpointGO.transform.SetParent(splineComputer.transform);
        }
    }
}
