using UnityEngine;

[DisallowMultipleComponent]
public sealed class CheckpointBehaviour : MonoBehaviour
{
    #region Parameters
    [SerializeField] private ParticleSystem particles = null;
    [SerializeField] private TagProvider tagProvider = null;
    [SerializeField] private MeshRenderer mesh = null;
    [SerializeField] private Color checkpointColor = Color.white;

    private ParticleSystem.MainModule mainModuleParticleSystem;
    #endregion

    #region MonoBehaviour API
    private void Start()
    {
        mainModuleParticleSystem = particles.main;
        mainModuleParticleSystem.startColor = checkpointColor;

        mesh.material.color = checkpointColor;
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.CompareTag(tagProvider.PlayerTag) && other.gameObject.TryGetComponent(out MeshRenderer meshRenderer))
        {
            meshRenderer.material.color = checkpointColor;
        }
    }
    #endregion
}
