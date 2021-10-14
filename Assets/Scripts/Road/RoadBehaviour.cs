using Dreamteck.Splines;
using UnityEngine;

[DisallowMultipleComponent]
[RequireComponent(typeof(SplineComputer))]
public sealed class RoadBehaviour : MonoBehaviour
{
    #region Parameters
    [SerializeField] private GameObject checkpoint = null;
    [SerializeField, Min(0.0f)] private float checkpointsSpawnDelta = 14.8f;
    [SerializeField] private Color[] colors = null;

    private SplineComputer splineComputer = null;
    #endregion

    #region MonoBehaviour API
    private void Awake()
    {
        splineComputer = GetComponent<SplineComputer>();
    }

    private void Start()
    {
        SpawnPoints();
    }
    #endregion

    #region Custom methods
    private void SpawnPoints()
    {
        float splineLength = splineComputer.CalculateLength();
        float fullLengthInPercent = 100, currentDistance = 0;
        int checkpointColorIndex = 0;

        while (currentDistance <= splineLength)
        {
            currentDistance += checkpointsSpawnDelta;

            double percent = ((currentDistance * fullLengthInPercent) / splineLength) / fullLengthInPercent;
            double savePercent = Mathf.Clamp01((float)percent);

            SplineSample splineSample = splineComputer.Evaluate(savePercent);

            GameObject checkpointGO = Instantiate(checkpoint, splineSample.position, splineSample.rotation);
            checkpointGO.transform.SetParent(transform);

            if (checkpoint.TryGetComponent(out CheckpointBehaviour checkpointBehaviour))
            {
                checkpointColorIndex = ++checkpointColorIndex % colors.Length;
                checkpointBehaviour.CheckpointColor = colors[checkpointColorIndex];
            }
        }
    }
    #endregion
}
