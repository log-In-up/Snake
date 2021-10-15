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
    private SpawnCheckpoints checkpoints = null;

    #endregion

    #region MonoBehaviour API
    private void Awake()
    {
        splineComputer = GetComponent<SplineComputer>();
    }

    private void Start()
    {
        checkpoints = new SpawnCheckpoints(splineComputer,checkpoint,colors,checkpointsSpawnDelta);

        checkpoints.CrateCheckpoints();
    }
    #endregion

    #region Custom methods

    #endregion
}
